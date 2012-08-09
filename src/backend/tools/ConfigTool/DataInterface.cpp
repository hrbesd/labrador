#include "DataInterface.h"
Node::Node(TreeItem *parent) : TreeItem(parent)
{
    type = TreeItem::NODE;
}

Node::~Node()
{
    qDeleteAll(ruleList);
    ruleList.clear();
}

TreeItem *Node::child(int number)
{
    return dynamic_cast<TreeItem*>(ruleList.value(number));
}
int Node::childCount() const
{
    return ruleList.size();
}
int Node::columnCount() const
{
    return 1;
}
QVariant Node::data(int column) const
{
    return name;
}
bool Node::insertChildren(int position, int count, int columns)
{
    if (position < 0 || position > ruleList.size())
        return false;

    for (int row = 0; row < count; ++row) {
        TreeItem *item = new Rule(this);
        ruleList.insert(position, dynamic_cast<Rule*>(item));
    }

    return true;
}
bool Node::insertColumns(int position, int columns)
{
    return true;
}
bool Node::removeChildren(int position, int count)
{
    if (position < 0 || position + count > ruleList.size())
        return false;

    for (int row = 0; row < count; ++row)
        delete ruleList.takeAt(position);

    return true;
}
bool Node::removeColumns(int position, int columns)
{
    return true;
}
int Node::childNumber() const
{
    if (parentItem)
        return dynamic_cast<Rule*>(parentItem)->nodeList.indexOf(const_cast<Node*>(this));

    return 0;
}
bool Node::setData(int column, const QVariant &value)
{
    if (column < 0 || column >= 1)
        return false;

    name=value.toString();
    return true;
}

Rule::Rule(TreeItem *parent) : TreeItem(parent)
{
    childRule=NULL;
    nextPageExpression.label = "nextPage";
    urlExpression.label = "url";
    titleExpression.label = "title";
    type = TreeItem::RULE;
}

Rule::~Rule()
{
    delete childRule;
    expressionList.clear();
    qDeleteAll(nodeList);
}

TreeItem *Rule::child(int number)
{
    return dynamic_cast<TreeItem*>(nodeList.value(number));
}
int Rule::childCount() const
{
    return nodeList.count();
}
int Rule::columnCount() const
{
    return 1;
}
QVariant Rule::data(int column) const
{
    return QVariant(dynamic_cast<Node*>(parentItem)->name+"Rule");
}
bool Rule::insertChildren(int position, int count, int columns)
{
    if (position < 0 || position > nodeList.size())
        return false;

    for (int row = 0; row < count; ++row) {
        TreeItem *item = new Node(this);
        Rule * tmpRule = new Rule(item);
        dynamic_cast<Node*>(item)->ruleList.append(tmpRule);

        nodeList.insert(position, dynamic_cast<Node*>(item));
    }

    return true;
}
bool Rule::insertColumns(int position, int columns){
    return true;
}
bool Rule::removeChildren(int position, int count)
{
    if (position < 0 || position + count > nodeList.size())
        return false;

    for (int row = 0; row < count; ++row)
        delete nodeList.takeAt(position);

    return true;
}
bool Rule::removeColumns(int position, int columns)
{
    return true;
}
int Rule::childNumber() const{
    if (parentItem)
        return  dynamic_cast<Node*>(parentItem)->ruleList.indexOf(const_cast<Rule*>(this));
    return 0;
}
bool Rule::setData(int column, const QVariant &value){
    return true;
}
