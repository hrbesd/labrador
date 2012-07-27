#include "yzspider.h"
#include <QDebug>
#include <QCoreApplication>
#include <QTextCodec>
#include <QDir>

YZSpider::YZSpider(QObject *parent) :
    QObject(parent)
  ,m_maxRuleRequestThreadNum(10)
  ,m_maxWebPageRequestThreadNum(10)
  ,m_webPageCount(0)
  ,m_finishParseRules(false)
{
    initParameters();
    m_networkAccessManager = new QNetworkAccessManager(this);
    m_configFileParser.parseWebsiteConfigFile(m_paramenters.value("--rule-dir"),m_website);
    m_webpageRequestThreadNum = m_website.threadLimit.toInt();
    //because we want columns to be downloaded in order, so only one thread
    m_maxRuleRequestThreadNum = 1;
    m_ruleRequestThreadNum = m_maxRuleRequestThreadNum;
    parseWebsiteData();
}

void YZSpider::downloadWebPage(Node *node)
{
    m_webpageRequestThreadNum--;
    QNetworkRequest request;
    QNetworkReply *reply;
    request.setUrl(QUrl(node->url));
    reply = m_networkAccessManager->get(request);
    m_webPageDownloadingTask.insert(reply,node);
    connect(reply,SIGNAL(finished()),this,SLOT(webPageDownloaded()));
    connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),this,SLOT(networkError(QNetworkReply::NetworkError)));
}

void YZSpider::downloadRule(RuleRequest ruleRequest)
{
    m_ruleRequestThreadNum--;
    QNetworkRequest request;
    QNetworkReply *reply;
    request.setUrl(QUrl(ruleRequest.url));
    reply = m_networkAccessManager->get(request);
    m_ruleDownloadingTask.insert(reply,ruleRequest);
    connect(reply,SIGNAL(finished()),this,SLOT(ruleRequestReply()));
    connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),this,SLOT(networkError(QNetworkReply::NetworkError)));
}

void YZSpider::webPageDownloaded()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(QObject::sender());
    QByteArray result = reply->readAll();
    Node *nodeItem = m_webPageDownloadingTask.take(reply);
    QString fileName = nodeItem->hashName;
    QDir folderDir;
    folderDir.mkpath(m_paramenters.value("--worker-dir"));
    folderDir.cd(m_paramenters.value("--worker-dir"));
    folderDir.mkpath(folderDir.absolutePath() + "/"+fileName.left(2));
    QFile file(folderDir.absolutePath() + "/"+fileName.left(2)+"/"+ fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qWarning("can't save webpage");
        return;
    }
    file.write((QString::number(reply->header(QNetworkRequest::LastModifiedHeader).toDateTime().toMSecsSinceEpoch())+"\n").toAscii());
    file.write(nodeItem->name.toUtf8());
    file.write("\n");
    file.write(reply->url().toString().toUtf8());
    file.write("\n");
    file.write(QTextCodec::codecForHtml(result)->toUnicode(result).toUtf8());
    qDebug()<<QString::number(m_webPageCount++)+ " web page downloaded";
    file.close();
    reply->deleteLater();
    m_webpageRequestThreadNum++;
    webpageDownloadScheduler();
}

void YZSpider::webpageDownloadScheduler()
{
    while(m_webpageRequestThreadNum>0&&m_webPageRequestTask.isEmpty()==false)
    {
        Node *nodeItem = m_webPageRequestTask.takeFirst();
        downloadWebPage(nodeItem);
    }
    if(m_webPageRequestTask.isEmpty()&&m_webpageRequestThreadNum==m_maxWebPageRequestThreadNum&& m_finishParseRules == true)
    {
        qDebug()<<"finish download webpages";
        exit(0);
    }
}

void YZSpider::ruleRequestScheduler()
{
    while(m_ruleRequestThreadNum>0&&m_ruleRequestTask.isEmpty()==false)
    {
        RuleRequest ruleRequest = m_ruleRequestTask.takeFirst();
        std::cout<<"parsing rule: "<<ruleRequest.url.toStdString()<<std::endl;
        downloadRule(ruleRequest);
    }
    if(m_ruleRequestTask.isEmpty()&&m_ruleRequestThreadNum==m_maxRuleRequestThreadNum)
    {
        qDebug()<<"finish parse rules";
        m_finishParseRules = true;
        QDir dir(m_paramenters.value("--shared-dir"));
        dir.mkpath(dir.absolutePath());
        outputWebsite(dir.absolutePath()+"/"+"dir.xml");
        webpageDownloadScheduler();
    }
}

void YZSpider::networkError(QNetworkReply::NetworkError error)
{
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(QObject::sender());
    YZLogger::Logger()->log(YZLogger::Error,reply->url().toString(),reply->errorString());
}

void YZSpider::ruleRequestReply()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(QObject::sender());
    QByteArray result = reply->readAll();
    QUrl baseUrl = reply->url();
    RuleRequest ruleRequest = m_ruleDownloadingTask.take(reply);
    parseRuleReply(ruleRequest.rule,result,baseUrl);
    parseNodeListData(ruleRequest.rule);
    reply->deleteLater();
    m_ruleRequestThreadNum++;
    ruleRequestScheduler();
}
//to do ... for now ,every rule has title regexp
void YZSpider::parseRuleReply(Rule *ruleItem, QByteArray &data, QUrl &baseUrl)
{
    QString strData = QString::fromUtf8(QTextCodec::codecForHtml(data)->toUnicode(data).toUtf8().data());
    //title && url
    QStringList urlStringList = parseRuleExpression(ruleItem->urlExpression,strData);
    QStringList titleStringList = parseRuleExpression(ruleItem->titleExpression,strData);
    if(urlStringList.size()!=titleStringList.size())
    {
        YZLogger::Logger()->log(YZLogger::Error,baseUrl.toString(),"url reg doesn't match title reg");
        return;
    }
    for(int i=0;i<urlStringList.size();i++)
    {
        QString url = baseUrl.resolved(urlStringList[i]).toString();
        if(!m_nodeUrlSet.contains(url))
        {
            m_nodeUrlSet.insert(url);
            Node nodeItem;
            nodeItem.name = titleStringList[i];
            nodeItem.url = url;
            ruleItem->nodeList.append(nodeItem);
        }
    }
    //next page
    QStringList nextPageStringList = parseRuleExpression(ruleItem->nextPageExpression,strData);
    for(int i=0;i<nextPageStringList.size();i++)
    {
        RuleRequest ruleRequest;
        ruleRequest.url = baseUrl.resolved(nextPageStringList[i]).toString();
        ruleRequest.rule = ruleItem;
        m_ruleRequestTask.append(ruleRequest);
    }
}

QStringList YZSpider::parseRuleExpression(Expression &expressionItem, const QString &strData)
{
    QStringList resultStrList;
    if(!expressionItem.value.isEmpty())
    {
        if(expressionItem.type=="RegExp")
        {
            QRegExp regExp(expressionItem.value);
            regExp.setMinimal(true);
            int index = 0;
            while ((index = regExp.indexIn(strData, index)) != -1) {
                index+=regExp.matchedLength();
                resultStrList.append(regExp.cap(1));
            }
        }
        else if(expressionItem.type=="JavaScript")
        {
            m_engine.evaluate(expressionItem.value);
            m_globalValue = m_engine.globalObject();
            m_spiderValue = m_globalValue.property("getYZSpiderResult");
            QScriptValueList args;
            args<<strData;
            QScriptValue result = m_spiderValue.call(QScriptValue(),args);
            resultStrList = result.toVariant().toStringList();
            if(expressionItem.executeOnlyOnce == "true")
            {
                expressionItem.value.clear();
            }
        }
    }
    return resultStrList;
}

void YZSpider::parseWebsiteData()
{
    m_websiteUrl.setUrl(m_website.node.url);
    parseNodeData(m_website.node);
    ruleRequestScheduler();
}

void YZSpider::parseNodeData(Node &nodeItem)
{
    //检查链接是否已经扫描过
    if(!m_resolvedNodes.contains(nodeItem.url))
    {
        if(!m_websiteUrl.isParentOf(QUrl(nodeItem.url)))
        {
            YZLogger::Logger()->log(YZLogger::Warning,nodeItem.url,QString("outside link:"));
        }
        nodeItem.hashName = QCryptographicHash::hash(QByteArray(nodeItem.url.toUtf8()),QCryptographicHash::Md5).toHex();
        if(nodeItem.ruleList.isEmpty())
        {
            m_webPageRequestTask.append(&nodeItem);
        }
        else{
            foreach(Rule *ruleItem,nodeItem.ruleList)
            {
                parseRuleData(ruleItem,nodeItem);
            }
        }
        m_resolvedNodes.insert(nodeItem.url);
    }
}
// to do...
void YZSpider::parseRuleData(Rule *ruleItem, Node &parentNode)
{
    parseNodeListData(ruleItem);
    if(!ruleItem->urlExpression.value.isEmpty())
    {
        RuleRequest ruleRequest;
        ruleRequest.rule = ruleItem;
        ruleRequest.url = parentNode.url;
        m_ruleRequestTask.append(ruleRequest);
    }
}

void YZSpider::parseNodeListData(Rule *ruleItem)
{
    if(ruleItem->childRule!=NULL)
    {
        for(int i=0;i<ruleItem->nodeList.size();i++)
        {
            if(ruleItem->nodeList[i].ruleList.isEmpty())
            {
                Rule *newRule = new Rule;
                newRule->childRule = ruleItem->childRule->childRule;
                newRule->maxPageCount = ruleItem->childRule->maxPageCount;
                newRule->titleExpression.copyFromExpression(ruleItem->childRule->titleExpression);
                newRule->nextPageExpression.copyFromExpression(ruleItem->childRule->nextPageExpression);
                newRule->urlExpression.copyFromExpression(ruleItem->childRule->urlExpression);
                ruleItem->nodeList[i].ruleList.append(newRule);
            }
        }
    }
    for(int i=0;i<ruleItem->nodeList.size();i++)
    {
        m_nodeUrlSet.insert(ruleItem->nodeList[i].url);
    }
    for(int i=0;i<ruleItem->nodeList.size();i++)
    {
        parseNodeData(ruleItem->nodeList[i]);
    }
}

void YZSpider::outputWebsite(QString fileName)
{
    YZXmlWriter::writeWebsiteItemToXml(m_website,fileName);
}

void YZSpider::initParameters()
{
    QStringList parametersList = QCoreApplication::arguments();
    foreach(QString parameter,parametersList)
    {
        QStringList tmpList = parameter.split('=');
        m_paramenters.insert(tmpList[0],tmpList.size()>1?tmpList[1]:QString(""));
    }

    if(m_paramenters.contains("--version"))
    {
        std::cout<<"Labrador Spider Version "<<BASE_VERSION<<endl;
        exit(0);
    }
    if(m_paramenters.contains("--log-file"))
    {
        YZLogger::logFilePath = m_paramenters.value("--log-file");
    }
    if(!m_paramenters.contains("--rule-dir"))
    {
        std::cerr<<"rule dir can't be empty, spider will exit now!"<<endl;
        exit(0);
    }
    if(!m_paramenters.contains("--worker-dir"))
    {
        std::cerr<<"worker dir can't be empty, spider will exit now!"<<endl;
        exit(0);
    }
    if(!m_paramenters.contains("--shared-dir"))
    {
        std::cerr<<"shared dir can't be empty, spider will exit now!"<<endl;
        exit(0);
    }
    std::cout<<"spider start to run..."<<std::endl;
}
