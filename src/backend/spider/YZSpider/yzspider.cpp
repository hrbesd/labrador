#include "yzspider.h"
#include <QDebug>
#include <QCoreApplication>
#include <QTextCodec>
#include <QDir>

YZSpider::YZSpider(QObject *parent) :
    QObject(parent),m_maxRuleRequestThreadNum(10),m_maxWebPageRequestThreadNum(10)
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

    YZLogger::Logger()->log("log something to test");


    m_webPageCount = 0;
    m_finishParseRules = false;
    m_networkAccessManager = new QNetworkAccessManager(this);
    QDir dir(m_paramenters.value("--rule-dir"));
    parseWebsiteConfigFile(dir.absolutePath()+"/"+"spider_config.xml");
    m_webpageRequestThreadNum = m_maxWebPageRequestThreadNum;
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
    m_webpageRequestThreadNum++;
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
        downloadRule(ruleRequest);
    }
    if(m_ruleRequestTask.isEmpty()&&m_ruleRequestThreadNum==m_maxRuleRequestThreadNum)
    {
        qDebug()<<"finish parse rules";
        m_finishParseRules = true;
        QDir dir(m_paramenters.value("--shared-dir"));
        dir.mkpath(dir.absolutePath());
        outputWebsite(dir.absolutePath()+"/"+m_website.node.name+"_dir.xml");
        webpageDownloadScheduler();
    }
}

void YZSpider::networkError(QNetworkReply::NetworkError error)
{
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(QObject::sender());
    YZLogger::Logger()->log(QString("error:")+reply->errorString()+reply->url().toString());
}

void YZSpider::ruleRequestReply()
{
    m_ruleRequestThreadNum++;
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(QObject::sender());
    QByteArray result = reply->readAll();
    QUrl baseUrl = reply->url();
    RuleRequest ruleRequest = m_ruleDownloadingTask.take(reply);
    parseRuleReply(ruleRequest.rule,result,baseUrl);
    parseNodeListData(ruleRequest.rule);
    reply->deleteLater();
    ruleRequestScheduler();
}
//to do ... for now ,every rule has title regexp
void YZSpider::parseRuleReply(Rule *ruleItem, QByteArray &data, QUrl &baseUrl)
{
    QString strData = QString::fromUtf8(QTextCodec::codecForHtml(data)->toUnicode(data).toUtf8().data());
    int posUrl = 0;
    int posTitle = 0;
    QRegExp urlRegExp(ruleItem->urlExpression.value);
    QRegExp titleRegExp(ruleItem->titleExpression.value);
    urlRegExp.setMinimal(true);
    titleRegExp.setMinimal(true);

    while ((posUrl = urlRegExp.indexIn(strData, posUrl)) != -1) {
        posUrl+=urlRegExp.matchedLength();
        if((posTitle = titleRegExp.indexIn(strData,posTitle)) ==-1)
        {
            qWarning()<<"rule error: url reg doesn't match title reg";
        }
        posTitle+=titleRegExp.matchedLength();
        QString url = baseUrl.resolved(urlRegExp.cap(1)).toString();
        if(!m_nodeUrlSet.contains(url))
        {
            m_nodeUrlSet.insert(url);
            Node nodeItem;
            nodeItem.name = titleRegExp.cap(1);
            nodeItem.url = url;
            ruleItem->nodeList.append(nodeItem);
        }
    }

    if(!ruleItem->nextPageExpression.value.isEmpty())
    {
        if(ruleItem->nextPageExpression.type=="RegExp")
        {
            QRegExp nextPageRegExp(ruleItem->nextPageExpression.value);
            if(nextPageRegExp.indexIn(strData)!=-1)
            {
                RuleRequest ruleRequest;
                ruleRequest.url = baseUrl.resolved(nextPageRegExp.cap(1)).toString();
                ruleRequest.rule = ruleItem;
                parseNextPage(ruleRequest);
            }
        }
        else if(ruleItem->nextPageExpression.type=="JavaScript")
        {
            m_engine.evaluate(ruleItem->nextPageExpression.value);
            m_globalValue = m_engine.globalObject();
            m_spiderValue = m_globalValue.property("getYZSpiderResult");
            QScriptValueList args;
            QScriptValue result = m_spiderValue.call(QScriptValue(),args);
            if(ruleItem->nextPageExpression.executeOnlyOnce == "true")
            {
                ruleItem->nextPageExpression.value.clear();
            }
            foreach(QString str,result.toVariant().toStringList())
            {
                RuleRequest ruleRequest;
                ruleRequest.url = baseUrl.resolved(str).toString();
                ruleRequest.rule = ruleItem;
                m_ruleRequestTask.append(ruleRequest);
            }
        }
    }
}

void YZSpider::parseWebsiteConfigFile(QString configFile)
{
    qDebug()<<configFile;
    QFile file(configFile);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qWarning("can't open config File");
        exit(0);
    }
    xmlReader.setDevice(&file);
    while (!xmlReader.atEnd()) {
        if(xmlReader.isStartElement())
        {
            if(xmlReader.name()=="website")
                parseWebsiteXml(xmlReader);
            else
            {
                qWarning()<<"invalid xml format";
            }
        }
        xmlReader.readNext();
    }
    file.close();
}

void YZSpider::parseWebsiteXml(QXmlStreamReader &reader)
{
    reader.readNext();
    while(!reader.atEnd())
    {
        if(reader.isEndElement()&&reader.name()=="website")
        {
            reader.readNext();
            return;
        }
        else if(reader.isStartElement())
        {
            if(reader.name()=="editor")
            {
                m_website.editor = reader.readElementText();
            }
            else if(reader.name()=="info")
            {
                m_website.info = reader.readElementText();
            }
            else if(reader.name()=="crawlTime")
            {
                m_website.crawlTime = reader.readElementText();
            }
            else if(reader.name()=="threadLimit")
            {
                m_website.threadLimit = reader.readElementText();
                m_maxRuleRequestThreadNum = m_website.threadLimit.toInt();
                m_maxWebPageRequestThreadNum = m_webpageRequestThreadNum;
            }
            else if(reader.name()=="node")
            {
                parseNodeXml(reader,m_website.node);
            }
        }
        reader.readNext();
    }

}

void YZSpider::parseNodeXml(QXmlStreamReader &reader, Node &node)
{
    reader.readNext();
    while(!reader.atEnd())
    {
        if(reader.isEndElement()&&reader.name()=="node")
        {
            reader.readNext();
            return;
        }
        else if(reader.isStartElement())
        {
            if(reader.name()=="name")
            {
                node.name = reader.readElementText();
            }
            else if(reader.name()=="url")
            {
                node.url = reader.readElementText();
            }
            else if(reader.name()=="refreshRate")
            {
                node.refreshRate = reader.readElementText();
            }
            else if(reader.name()=="ruleList")
            {
                parseRuleListXml(reader,node.ruleList);
            }
        }
        reader.readNext();
    }
}

void YZSpider::parseNodeListXml(QXmlStreamReader &reader, QList<Node> &parentNodeList)
{
    reader.readNext();
    while(!reader.atEnd())
    {
        if(reader.isEndElement()&&reader.name()=="nodeList")
        {
            reader.readNext();
            return;
        }
        else if(reader.isStartElement())
        {
            if(reader.name()=="node")
            {
                Node newNode;
                parentNodeList<<newNode;
                parseNodeXml(reader,parentNodeList.last());
            }
        }
        reader.readNext();
    }
}

void YZSpider::parseRuleListXml(QXmlStreamReader &reader, QList<Rule *> &parentRuleList)
{
    reader.readNext();
    while(!reader.atEnd())
    {
        if(reader.isEndElement()&&reader.name()=="ruleList")
        {
            reader.readNext();
            return;
        }
        else if(reader.isStartElement())
        {
            if(reader.name()=="rule")
            {
                Rule* newRule = new Rule;
                parentRuleList<<newRule;
                parseRuleXml(reader,parentRuleList.last());
            }
        }
        reader.readNext();
    }
}


void YZSpider::parseRuleXml(QXmlStreamReader &reader, Rule *rule)
{
    reader.readNext();
    while(!reader.atEnd())
    {
        if(reader.isEndElement()&&reader.name()=="rule")
        {
            reader.readNext();
            return;
        }
        else if(reader.isStartElement())
        {
            if(reader.name()=="maxPageCount")
            {
                rule->maxPageCount = reader.readElementText();
            }
            else if(reader.name()=="childRule")
            {
                parseChildRuleXml(reader,rule);
            }
            else if(reader.name()=="nodeList")
            {
                parseNodeListXml(reader,rule->nodeList);
            }
            else if(reader.name()=="expressionList")
            {
                parseExpressionListXml(reader,rule);
            }
        }
        reader.readNext();
    }
}

void YZSpider::parseExpressionListXml(QXmlStreamReader &reader, Rule *rule)
{
    reader.readNext();
    while(!reader.atEnd())
    {
        if(reader.isEndElement()&&reader.name()=="expressionList")
        {
            reader.readNext();
            return;
        }
        else if(reader.isStartElement())
        {
            if(reader.name()=="expression")
            {
                Expression newExpression;
                newExpression.executeOnlyOnce.append(reader.attributes().value("executeOnlyOnce"));
                newExpression.label.append(reader.attributes().value("label"));
                newExpression.value.append(reader.attributes().value("value"));
                newExpression.type.append(reader.attributes().value("type"));
                if(newExpression.label=="title")
                {
                    rule->titleExpression.copyFromExpression(newExpression);
                }
                else if(newExpression.label=="url")
                {
                    rule->urlExpression.copyFromExpression(newExpression);
                }
                else if(newExpression.label=="nextPage")
                {
                    rule->nextPageExpression.copyFromExpression(newExpression);
                }
                else
                {
                    rule->expressionList<<newExpression;
                }
            }
        }
        reader.readNext();
    }
}

void YZSpider::parseChildRuleXml(QXmlStreamReader &reader, Rule *rule)
{
    reader.readNext();
    while(!reader.atEnd())
    {
        if(reader.isEndElement()&&reader.name()=="childRule")
        {
            reader.readNext();
            break;
        }
        else if(reader.isStartElement())
        {
            if(reader.name()=="rule")
            {
                Rule* newRule = new Rule;
                rule->childRule = newRule;
                parseRuleXml(reader,rule->childRule);
            }
        }
        reader.readNext();
    }
}

void YZSpider::parseWebsiteData()
{
    m_websiteUrl.setUrl(m_website.node.url);
    parseNodeData(m_website.node);
    ruleRequestScheduler();
}

void YZSpider::parseNodeData(Node &nodeItem)
{
    if(!m_resolvedNodes.contains(nodeItem.url))
    {
        if(!m_websiteUrl.isParentOf(QUrl(nodeItem.url)))
        {
            YZLogger::Logger()->log(QString("outside link:")+nodeItem.url);
        }
        nodeItem.hashName = QCryptographicHash::hash(QByteArray(nodeItem.url.toUtf8()),QCryptographicHash::Md5).toHex();
        if(nodeItem.ruleList.isEmpty())
        {
            m_webPageRequestTask.append(&nodeItem);
        }
        foreach(Rule *ruleItem,nodeItem.ruleList)
        {
            parseRuleData(ruleItem,nodeItem);
        }
        m_resolvedNodes.insert(nodeItem.url);
    }
}
// to do...
void YZSpider::parseRuleData(Rule *ruleItem, Node &parentNode)
{
    if(ruleItem->urlExpression.value.isEmpty())
    {
        parseNodeListData(ruleItem);
    }
    else
    {
        RuleRequest ruleRequest;
        ruleRequest.rule = ruleItem;
        ruleRequest.url = parentNode.url;
        m_ruleRequestTask.append(ruleRequest);
        // to do..       parseNodeListData(ruleItem);
    }
}

void YZSpider::parseNodeListData(Rule *ruleItem)
{
    if(ruleItem->childRule!=NULL)
    {
        for(int i=0;i<ruleItem->nodeList.size();i++)
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
    for(int i=0;i<ruleItem->nodeList.size();i++)
    {
        parseNodeData(ruleItem->nodeList[i]);
    }
}

void YZSpider::parseNextPage(RuleRequest ruleRequest)
{
    m_ruleRequestTask.append(ruleRequest);
    ruleRequestScheduler();
}

void YZSpider::outputWebsite(QString fileName)
{
    YZXmlWriter::writeWebsiteItemToXml(m_website,fileName);
}
