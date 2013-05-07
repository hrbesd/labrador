#include "forerunner.h"
#include <QDebug>
#include <QCoreApplication>
#include <QTextCodec>
#include <QDir>

ForeRunner::ForeRunner(QObject *parent) :
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
    if(m_website.codecName.isEmpty())
    {
        codec = QTextCodec::codecForName("utf8");
    }
    else
    {
        codec = QTextCodec::codecForName(m_website.codecName.toUtf8());
    }
    parseWebsiteData();
}

void ForeRunner::downloadRule(RuleRequest ruleRequest)
{
    m_ruleRequestThreadNum--;
    QNetworkRequest request;
    QNetworkReply *reply;
    QByteArray encodedUrl;
    encodeURI(ruleRequest.url, encodedUrl);
    QUrl requestUrl;
    requestUrl.setEncodedUrl (encodedUrl);
    request.setUrl(requestUrl);
    reply = m_networkAccessManager->get(request);
    m_ruleDownloadingTask.insert(reply,ruleRequest);
    connect(reply,SIGNAL(finished()),this,SLOT(ruleRequestReply()));
    connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),this,SLOT(networkError(QNetworkReply::NetworkError)));
}

void ForeRunner::encodeURI (const QString &str, QByteArray &outArr)
{
    QTextCodec *codec = QTextCodec::codecForName("GB2312");
    if(codec->canEncode(str)) {
        QByteArray tmpArr;
        tmpArr = codec->fromUnicode(str);
        for(int i=0,size = tmpArr.length();i<size;i++){
            char ch = tmpArr.at(i);
            if(ch < 128 && ch > 0){
                outArr.append(ch);
            }else{
                uchar low = ch & 0xff;
                char c[3];
                sprintf(c,"%02X",low);
                outArr.append("%").append(c);
            }
        }
    }
}

void ForeRunner::ruleRequestScheduler()
{
    while(m_ruleRequestThreadNum>0&&m_ruleRequestTask.isEmpty()==false)
    {
        RuleRequest ruleRequest = m_ruleRequestTask.takeFirst();
        qDebug()<<"parsing rule: "<<ruleRequest.url;
        downloadRule(ruleRequest);
    }
    if(m_ruleRequestTask.isEmpty()&&m_ruleRequestThreadNum==m_maxRuleRequestThreadNum)
    {
        qDebug()<<"finish parse rules";
        m_finishParseRules = true;
        QDir dir(m_paramenters.value("--shared-dir"));
        dir.mkpath(dir.absolutePath());
        outputWebsite(dir.absolutePath()+"/"+"dir.xml");
        exit(0);
    }
}

void ForeRunner::networkError(QNetworkReply::NetworkError error)
{
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(QObject::sender());
    YZLogger::Logger()->log(YZLogger::Error,reply->url().toString(),reply->errorString());
}

void ForeRunner::ruleRequestReply()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(QObject::sender());
    QByteArray result = codec->toUnicode(reply->readAll()).toUtf8();
    QUrl baseUrl = reply->url();
    RuleRequest ruleRequest = m_ruleDownloadingTask.take(reply);
    parseRuleReply(ruleRequest.rule,result,baseUrl);
    parseNodeListData(ruleRequest.rule);
    reply->deleteLater();
    m_ruleRequestThreadNum++;
    ruleRequestScheduler();
}
//to do ... for now ,every rule has title regexp
void ForeRunner::parseRuleReply(Rule *ruleItem, QByteArray &data, QUrl &baseUrl)
{
    QString strData = QString::fromUtf8(data.data());
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
            //20130505             
            nodeItem.title=nodeItem.name;           
            QString     temp=">"+nodeItem.name;
            int i_start=0;
            int i_end=strData.indexOf(temp);
            temp = strData.mid(i_start,i_end); 
            i_start=temp.lastIndexOf ("<a ");
            temp = temp.mid(i_start,i_end+1);              
            //QStringList a_titleStringList =  parseRuleExpression(ruleItem->titleExpression,strData);
            //nodeItem.title=ruleItem->titleExpression.value;
//            QRegExp rxlen(" title\\s*=\\s*[^\\>]*(\"|')");
            QRegExp rxlen(" title\\s*=\\s*(\"|')[^\\\"|\\\']*(\"|')");
            int pos = rxlen.indexIn(temp);
            if (pos > -1) {
                  temp=rxlen.cap(0);   
                nodeItem.title=temp.mid(7,temp.length());
                
            }
            
            

            nodeItem.url = url;
            ruleItem->nodeList.append(nodeItem);
        }
    }
    //next page
    QStringList nextPageStringList = parseRuleExpression(ruleItem->nextPageExpression,strData);
    for(int i=0;i<nextPageStringList.size();i++)
    {
        QString ruleUrl = baseUrl.resolved(nextPageStringList[i]).toString();
        if(!m_resolvedRules.contains(ruleUrl))
        {
            m_resolvedRules.insert(ruleUrl);
            RuleRequest ruleRequest;
            ruleRequest.url = ruleUrl;
            ruleRequest.rule = ruleItem;
            m_ruleRequestTask.append(ruleRequest);
        }
    }
}

QStringList ForeRunner::parseRuleExpression(Expression &expressionItem, const QString &strData)
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

void ForeRunner::parseWebsiteData()
{
    m_websiteUrl.setUrl(m_website.node.url);
    parseNodeData(m_website.node);
    ruleRequestScheduler();
}

bool ForeRunner::checkWhetherNodeExists(Node &nodeItem)
{
    QString fileName = nodeItem.hashName;
    QDir folderDir(m_paramenters.value("--worker-dir"));
    QFile file(folderDir.absolutePath() + "/"+fileName.left(2)+"/"+ fileName);
    return file.exists();
}

void ForeRunner::parseNodeData(Node &nodeItem)
{
    //检查链接是否已经扫描过
    if(!m_resolvedNodes.contains(nodeItem.url))
    {
        if(!m_websiteUrl.isParentOf(QUrl(nodeItem.url)))
        {
            YZLogger::Logger()->log(YZLogger::Warning,nodeItem.url,QString("outside link"));
        }
        nodeItem.hashName = QCryptographicHash::hash(QByteArray(nodeItem.url.toUtf8()),QCryptographicHash::Md5).toHex();

        foreach(Rule *ruleItem,nodeItem.ruleList)
        {
            parseRuleData(ruleItem,nodeItem);
        }

        m_resolvedNodes.insert(nodeItem.url);
    }
}
// to do...
void ForeRunner::parseRuleData(Rule *ruleItem, Node &parentNode)
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

void ForeRunner::parseNodeListData(Rule *ruleItem)
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

void ForeRunner::outputWebsite(QString fileName)
{
    YZXmlWriter::writeWebsiteItemToXml(m_website,fileName);
}

void ForeRunner::initParameters()
{
    QStringList parametersList = QCoreApplication::arguments();
    foreach(QString parameter,parametersList)
    {
        QStringList tmpList = parameter.split('=');
        m_paramenters.insert(tmpList[0],tmpList.size()>1?tmpList[1]:QString(""));
    }

    if(m_paramenters.contains("--version"))
    {
        std::cout<<"Labrador ForeRunner Version "<<BASE_VERSION<<endl;
        exit(0);
    }
    if(m_paramenters.contains("--log-file"))
    {
        YZLogger::logFilePath = m_paramenters.value("--log-file");
    }
    if(!m_paramenters.contains("--rule-dir"))
    {
        std::cerr<<"rule dir can't be empty, foreRunner will exit now!"<<endl;
        exit(0);
    }
    if(!m_paramenters.contains("--shared-dir"))
    {
        std::cerr<<"shared dir can't be empty, foreRunner will exit now!"<<endl;
        exit(0);
    }
    std::cout<<"ForeRunner start to run..."<<std::endl;
}
