#include "DataInterface.h"

Node::Node()
{
    itemType = Item::NODE;
}

Node::~Node()
{
    qDeleteAll(ruleList);
}

TreeItem::TreeItem(TreeItem *parent, Item *data)
{
    itemType = Item::TREE;
    parentItem = parent;
    dataItem = data;
}

TreeItem::~TreeItem()
{
    qDeleteAll(childItems);
}

TreeItem* TreeItem::child(int number)
{
    return childItems.value(number);
}

int TreeItem::childCount() const
{
    return childItems.size();
}

int TreeItem::columnCount() const
{
    return 1;
}

QVariant TreeItem::data(int column) const
{
    if(dataItem)
    {
        if(dataItem->itemType==Item::NODE)
        {
            return dynamic_cast<Node*>(dataItem)->name;
        }
        else if(dataItem->itemType==Item::RULE)
        {
            if(parentItem)
            {
                return QVariant(dynamic_cast<Node*>(parentItem->dataItem)->name+"Rule");
            }
        }
    }
}

bool TreeItem::appendChild(TreeItem *childItem)
{
    this->childItems.append(childItem);
}

bool TreeItem::insertChildren(int position, int count, int columns)
{
    if(dataItem)
    {
        if(dataItem->itemType==Item::NODE)
        {
            Node *tmpNode = dynamic_cast<Node*>(dataItem);
            if (position < 0 || position > tmpNode->ruleList.size())
                return false;

            for (int row = 0; row < count; ++row) {
                Rule *item = new Rule();
                tmpNode->ruleList.insert(position, item);
                TreeItem *tmpTreeItem = new TreeItem(this,item);
                this->childItems.insert(position,tmpTreeItem);
            }
            return true;
        }
        else if(dataItem->itemType==Item::RULE)
        {
            Rule* tmpRule = dynamic_cast<Rule*>(dataItem);
            if (position < 0 || position > tmpRule->nodeList.size())
                return false;

            for (int row = 0; row < count; ++row) {
                Node *node = new Node();
                tmpRule->nodeList.insert(position, node);
                TreeItem *tmpTreeItem = new TreeItem(this,node);
                this->childItems.insert(position,tmpTreeItem);
            }
            return true;
        }
    }
}

bool TreeItem::insertColumns(int position, int columns)
{
    return false;
}

bool TreeItem::removeChildren(int position, int count)
{
    if(dataItem)
    {
        if(dataItem->itemType==Item::NODE)
        {
            Node *tmpNode = dynamic_cast<Node*>(dataItem);
            if (position < 0 || position + count > tmpNode->ruleList.size())
                return false;

            for (int row = 0; row < count; ++row)
            {
                delete tmpNode->ruleList.takeAt(position);
                delete this->childItems.takeAt(position);
            }

            return true;
        }
        else if(dataItem->itemType==Item::RULE)
        {
            Rule* tmpRule = dynamic_cast<Rule*>(dataItem);
            if (position < 0 || position + count > tmpRule->nodeList.size())
                return false;

            for (int row = 0; row < count; ++row)
            {
                tmpRule->nodeList.removeAt(position);
                delete this->childItems.takeAt(position);
            }

            return true;
        }
    }
}

bool TreeItem::removeColumns(int position, int columns)
{
    return false;
}

int TreeItem::childNumber() const
{
    if (parentItem)
        return parentItem->childItems.indexOf(const_cast<TreeItem*>(this));

    return 0;
}

bool TreeItem::setData(int column, const QVariant &value)
{
    if(dataItem)
    {
        if(dataItem->itemType==Item::NODE)
        {
            if (column < 0 || column >= 1)
                return false;

            dynamic_cast<Node*>(dataItem)->name=value.toString();
            return true;
        }
        else if(dataItem->itemType==Item::RULE)
        {
            return false;
        }
    }

    return false;
}

Rule::Rule()
{
    childRule=NULL;
    nextPageExpression.label = "nextPage";
    urlExpression.label = "url";
    titleExpression.label = "title";
    itemType = Item::RULE;
}

Rule::~Rule()
{
    delete childRule;
    qDeleteAll(nodeList);
}
