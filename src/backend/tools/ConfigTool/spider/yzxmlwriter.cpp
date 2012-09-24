#include "yzxmlwriter.h"
#include <QDebug>

YZXmlWriter::YZXmlWriter(QObject *parent) :
    QObject(parent)
{
}

void YZXmlWriter::writeWebsiteItemToXml(WebSite &websiteItem, QString fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qWarning()<<"can't open xml file";
        return;
    }

    QXmlStreamWriter writer(&file);
    writer.setAutoFormatting(true);
    writer.writeStartDocument();
    writer.writeStartElement("website");
    writer.writeTextElement("editor", websiteItem.editor);
    writer.writeTextElement("info",websiteItem.info);
    writer.writeTextElement("version","0.1.1");
    writer.writeTextElement("crawlTime",websiteItem.crawlTime);
    writer.writeTextElement("threadLimit",websiteItem.threadLimit);
    writer.writeTextElement("codecName",websiteItem.codecName);
    YZXmlWriter::writeNodeItemToXml(&(websiteItem.node),writer);

    writer.writeEndElement();
    writer.writeEndDocument();
    file.close();
}

void YZXmlWriter::writeNodeItemToXml(const Node *nodeItem, QXmlStreamWriter &writer)
{
    writer.writeStartElement("node");
    writer.writeTextElement("name",nodeItem->name);
    writer.writeTextElement("url",nodeItem->url);
    writer.writeTextElement("refreshRate",nodeItem->refreshRate);
    writer.writeStartElement("ruleList");
    foreach(Rule * ruleItem, nodeItem->ruleList)
    {
        writeRuleItemToXml(ruleItem,writer);
    }
    writer.writeEndElement();
    writer.writeEndElement();
}

void YZXmlWriter::writeRuleItemToXml(const Rule *ruleItem, QXmlStreamWriter &writer)
{
    writer.writeStartElement("rule");
    writer.writeStartElement("expressionList");
    writeExpressionItemToXml(ruleItem->nextPageExpression,writer);
    writeExpressionItemToXml(ruleItem->urlExpression,writer);
    writeExpressionItemToXml(ruleItem->titleExpression,writer);
    foreach(Expression expressionItem, ruleItem->expressionList)
    {
        writeExpressionItemToXml(expressionItem,writer);
    }
    writer.writeEndElement();
    writer.writeTextElement("maxPageCount",ruleItem->maxPageCount);
    writer.writeStartElement("childRule");
    if(ruleItem->childRule!=NULL)
    {
        writeRuleItemToXml(ruleItem->childRule,writer);
    }
    writer.writeEndElement();
    writer.writeStartElement("nodeList");
    foreach(Node* nodeItem, ruleItem->nodeList)
    {
        writeNodeItemToXml(nodeItem,writer);
    }
    writer.writeEndElement();
    writer.writeEndElement();
}

void YZXmlWriter::writeExpressionItemToXml(const Expression &expressionItem, QXmlStreamWriter &writer)
{
    writer.writeEmptyElement("expression");
    writer.writeAttribute("type",expressionItem.type);
    writer.writeAttribute("executeOnlyOnce",expressionItem.executeOnlyOnce);
    writer.writeAttribute("label",expressionItem.label);
    writer.writeAttribute("value",expressionItem.value);
}
