#include "yzspider.h"
#include <QDebug>
#include <QCoreApplication>
#include <QTextCodec>
#include <QDir>

YZSpider::YZSpider(QObject *parent) :
    QObject(parent)
{
    m_webpageRequestThreadNum = m_maxWebPageRequestThreadNum;
    m_ruleRequestThreadNum = m_maxRuleRequestThreadNum;
    m_webPageCount = 0;
    m_finishParseRules = false;
    m_networkAccessManager = new QNetworkAccessManager(this);
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
    folderDir.mkpath(QDir::currentPath()+"/webpage/originalFiles");
    folderDir.cd("webpage/originalFiles");
    QFile file(folderDir.absolutePath() + "/"+ fileName);
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
        qApp->exit();
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
        webpageDownloadScheduler();
    }
}

void YZSpider::networkError(QNetworkReply::NetworkError error)
{
    qDebug()<<"error:"+error;
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
    QRegExp urlRegExp(ruleItem->urlRegExp);
    QRegExp titleRegExp(ruleItem->nameRegExp);
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
            Node nodeItem;
            nodeItem.name = titleRegExp.cap(1);
            nodeItem.url = url;
            ruleItem->nodeList.append(nodeItem);
            m_nodeUrlSet.insert(url);
            YZLogger::Logger()->log(nodeItem.name+":"+nodeItem.url);
        }
    }
    if(!ruleItem->nextPageRegExp.isEmpty())
    {
        QRegExp nextPageRegExp(ruleItem->nextPageRegExp);
        if(nextPageRegExp.indexIn(strData)!=-1)
        {
            RuleRequest ruleRequest;
            ruleRequest.url = baseUrl.resolved(nextPageRegExp.cap(1)).toString();
            ruleRequest.rule = ruleItem;
            parseNextPage(ruleRequest);
        }
    }
}

void YZSpider::parseConfigFile(QString configFile)
{
    QFile file(configFile);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qWarning("can't open config File");
        return;
    }
    QXmlStreamReader xmlReader(&file);
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
    parseWebsiteData();
}

void YZSpider::parseWebsiteXml(QXmlStreamReader &reader)
{
    reader.readNext();
    while(!reader.atEnd())
    {
        if(reader.isEndElement()&&reader.name()=="website")
        {
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
        if(reader.isEndElement()&&reader.name()=="NodeList")
        {
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
            return;
        }
        else if(reader.isStartElement())
        {
            if(reader.name()=="urlRegExp")
            {
                rule->urlRegExp = reader.readElementText();
            }
            else if(reader.name()=="nextPageRegExp")
            {
                rule->nextPageRegExp = reader.readElementText();
            }
            else if(reader.name()=="maxPageCount")
            {
                rule->maxPageCount = reader.readElementText();
            }
            else if(reader.name()=="nameRegExp")
            {
                rule->nameRegExp = reader.readElementText();
            }
            else if(reader.name()=="childRule")
            {
                reader.readNext();
                while(!reader.atEnd())
                {
                    if(reader.isEndElement()&&reader.name()=="childRule")
                    {
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
            else if(reader.name()=="nodeList")
            {
                parseNodeListXml(reader,rule->nodeList);
            }
        }
        reader.readNext();
    }
}

void YZSpider::parseWebsiteData()
{
    parseNodeData(m_website.node);
    ruleRequestScheduler();
}

void YZSpider::parseNodeData(Node &nodeItem)
{

    foreach(Rule *ruleItem,nodeItem.ruleList)
    {
        parseRuleData(ruleItem,nodeItem);
    }
}

void YZSpider::parseRuleData(Rule *ruleItem, Node &parentNode)
{
    if(ruleItem->urlRegExp.isEmpty())
    {
        parseNodeListData(ruleItem);
    }
    else
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
            Rule *newRule = new Rule;
            newRule->childRule = ruleItem->childRule->childRule;
            newRule->maxPageCount = ruleItem->childRule->maxPageCount;
            newRule->nameRegExp = ruleItem->childRule->nameRegExp;
            newRule->nextPageRegExp = ruleItem->childRule->nextPageRegExp;
            newRule->urlRegExp = ruleItem->childRule->urlRegExp;
            ruleItem->nodeList[i].ruleList.append(newRule);
        }
    }
    foreach(Node nodeItem, ruleItem->nodeList)
    {
        parseNodeData(nodeItem);
    }
}

void YZSpider::parseNextPage(RuleRequest ruleRequest)
{
    m_ruleRequestTask.append(ruleRequest);
    ruleRequestScheduler();
}
