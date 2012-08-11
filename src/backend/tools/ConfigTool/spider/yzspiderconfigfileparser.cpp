#include "yzspiderconfigfileparser.h"

YZSpiderConfigFileParser::YZSpiderConfigFileParser(QObject *parent) :
    QObject(parent)
{
}

void YZSpiderConfigFileParser::parseWebsiteXml(QXmlStreamReader &reader, WebSite &m_website)
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
            }
            else if(reader.name()=="node")
            {
                parseNodeXml(reader,&(m_website.node));
            }
        }
        reader.readNext();
    }
}

void YZSpiderConfigFileParser::parseNodeXml(QXmlStreamReader &reader, Node *node)
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
                node->name = reader.readElementText();
            }
            else if(reader.name()=="url")
            {
                node->url = reader.readElementText();
            }
            else if(reader.name()=="refreshRate")
            {
                node->refreshRate = reader.readElementText();
            }
            else if(reader.name()=="ruleList")
            {
                parseRuleListXml(reader,node->ruleList);
            }
        }
        reader.readNext();
    }
}

void YZSpiderConfigFileParser::parseNodeListXml(QXmlStreamReader &reader, QList<Node *> &parentNodeList)
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
                Node* newNode= new Node();
                parentNodeList<<newNode;
                parseNodeXml(reader,parentNodeList.last());
            }
        }
        reader.readNext();
    }
}

void YZSpiderConfigFileParser::parseRuleListXml(QXmlStreamReader &reader, QList<Rule *> &parentRuleList)
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


void YZSpiderConfigFileParser::parseRuleXml(QXmlStreamReader &reader, Rule *rule)
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

void YZSpiderConfigFileParser::parseExpressionListXml(QXmlStreamReader &reader, Rule *rule)
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

void YZSpiderConfigFileParser::parseChildRuleXml(QXmlStreamReader &reader, Rule *rule)
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

void YZSpiderConfigFileParser::parseWebsiteConfigFile(QString ruleDir, WebSite &m_website)
{
    QDir dir(ruleDir);
    QString configFile = dir.absolutePath()+"/"+"spider_config.xml";
    QFile file(configFile);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qWarning("can't open config File");
        exit(0);
    }
    QXmlStreamReader xmlReader;
    xmlReader.setDevice(&file);
    while (!xmlReader.atEnd()) {
        if(xmlReader.isStartElement())
        {
            if(xmlReader.name()=="website")
                parseWebsiteXml(xmlReader,m_website);
            else
            {
                std::cerr<<"invalid xml format"<<std::endl;
            }
        }
        xmlReader.readNext();
    }
    file.close();
}
