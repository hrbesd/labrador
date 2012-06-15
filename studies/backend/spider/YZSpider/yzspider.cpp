#include "yzspider.h"
#include <QDebug>
#include <QCoreApplication>
#include <QTextCodec>
#include <QDir>

YZSpider::YZSpider(QObject *parent) :
    QObject(parent)
{
    m_threadLimit = 10;
    m_webPageCount = 0;
    m_networkAccessManager = new QNetworkAccessManager(this);
}

YZSpider::YZSpider(QString whiteListFileName, QObject *parent)
{
    m_threadLimit = 10;
    m_networkAccessManager = new QNetworkAccessManager(this);
}

void YZSpider::downloadWebPage(QString url)
{
    m_threadLimit--;
    QNetworkRequest request;
    QNetworkReply *reply;
    request.setUrl(QUrl(url));
    reply = m_networkAccessManager->get(request);
    connect(reply,SIGNAL(finished()),this,SLOT(webPageDownloaded()));
    connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),this,SLOT(networkError(QNetworkReply::NetworkError)));
}

void YZSpider::webPageDownloaded()
{
    m_threadLimit++;
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(QObject::sender());
    QByteArray result = reply->readAll();
    QString fileName = QCryptographicHash::hash(QByteArray(reply->url().toString().toUtf8()),QCryptographicHash::Md5).toHex();
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
    file.write(QTextCodec::codecForHtml(result)->toUnicode(m_titleLinkMap.value(reply->url().toString())).toUtf8());
    file.write("\n");
    file.write(reply->url().toString().toUtf8());
    file.write("\n");
    file.write(QTextCodec::codecForHtml(result)->toUnicode(result).toUtf8());
    qDebug()<<QString::number(m_webPageCount++)+ " web page downloaded";
    file.close();
    reply->deleteLater();
    downloadScheduler();
}

void YZSpider::networkError(QNetworkReply::NetworkError error)
{
    qDebug()<<"error:"+error;
}

void YZSpider::parseLinks(QString url)
{
    QNetworkRequest request;
    QNetworkReply *reply;
    request.setUrl(QUrl(url));
    reply = m_networkAccessManager->get(request);
    connect(reply,SIGNAL(finished()),this,SLOT(parseLinksReply()));
    connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),this,SLOT(networkError(QNetworkReply::NetworkError)));
}

void YZSpider::nodeRequestReply()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(QObject::sender());
    QByteArray result = reply->readAll();
    QUrl baseUrl = reply->url();

    reply->deleteLater();
}

void YZSpider::parseLinksReply()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(QObject::sender());
    QByteArray result = reply->readAll();
    QUrl baseUrl = reply->url();
    int index = -1;
    while(1)
    {
        index = result.indexOf("<a class=\"f3348\"",index+1);
        if(index==-1)
        {
            break;
        }
        QUrl subUrl = getSubUrl(result,index);
        QByteArray title = getTitle(result,index);
        if(subUrl.isRelative())
        {
            m_innerLinks.insert(baseUrl.resolved(subUrl).toString());
            m_titleLinkMap.insert(baseUrl.resolved(subUrl).toString(),title);
        }
        else
        {
            m_outerLinks.insert(subUrl.toString());
            m_titleLinkMap.insert(subUrl.toString(),title);
        }
    }

    index = result.indexOf("class=\"Next\">");
    if(index==-1)
    {
        downloadScheduler();
    }
    else
    {
        index = result.lastIndexOf("<a",index);
        parseLinks(baseUrl.resolved(QUrl(getSubUrl(result,index))).toString());
    }

    reply->deleteLater();
}

QString YZSpider::getSubUrl(QByteArray &data, int index)
{
    int startIndex = data.indexOf("href=",index)+6;
    int endIndex = data.indexOf("\"",startIndex);
    return QString(data.mid(startIndex,endIndex - startIndex));
}

QByteArray YZSpider::getTitle(QByteArray &data, int index)
{
    int startIndex = data.indexOf("title=",index)+7;
    int endIndex = data.indexOf("\"",startIndex);
    return data.mid(startIndex,endIndex - startIndex);
}

void YZSpider::downloadScheduler()
{
    while(m_threadLimit>=0&&m_innerLinks.isEmpty()==false)
    {
        QString url = *(m_innerLinks.begin());
        m_innerLinks.erase(m_innerLinks.begin());
        downloadWebPage(url);
    }
    if(m_innerLinks.isEmpty()&&m_threadLimit==10)
    {
        qDebug()<<"finish";
        qApp->exit();
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
    qDebug()<<"finish";
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

}

void YZSpider::parseNodeData()
{

}
