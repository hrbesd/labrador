#ifndef DATAINTERFACE_H
#define DATAINTERFACE_H
#include <QString>
#include <QList>
#include <QVariant>
class Node;
class Rule;

class Item{
public:
    enum Type{
        NODE,
        RULE,
        TREE
    };

    virtual Type getType()
    {
        return itemType;
    }
    Type itemType;
};

class TreeItem : public Item
{
public:
    TreeItem(TreeItem *parent ,Item* data);
    ~TreeItem();
    TreeItem *child(int number);
    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const;
    bool appendChild(TreeItem *childItem);
    bool insertChildren(int position, int count, int columns);
    bool insertColumns(int position, int columns);
    TreeItem *parent()
    {
        return parentItem;
    }
    bool removeChildren(int position, int count);
    bool removeColumns(int position, int columns);
    int childNumber() const;
    bool setData(int column, const QVariant &value);
    TreeItem *parentItem;
    Item *dataItem;
    QList<TreeItem*> childItems;
};

struct Expression
{
    Expression(QString labelPara = "",QString valuePara = "") {
        label =  labelPara;
        value = valuePara;
    }
    void copyFromExpression(const Expression& otherExpression)
    {
        this->type = otherExpression.type;
        this->label = otherExpression.label;
        this->value = otherExpression.value;
        this->executeOnlyOnce = otherExpression.executeOnlyOnce;
    }
    QString type;         //value type: {RegExp, JavaScript}
    QString executeOnlyOnce;     //execute only once flag : {true,false}
    QString label;     // used as key
    QString value;     // used as value
};

class Rule : public Item
{
public:
    Rule() ;
    ~Rule();
    QList<Expression> expressionList;
    Expression nextPageExpression;
    Expression urlExpression;
    Expression titleExpression;
    QString maxPageCount;
    QList<Node*> nodeList;
    Rule* childRule;
};

class Node : public Item
{
public:
    Node();
    ~Node();
    QString url;
    QString name;
    QString refreshRate;
    QList<Rule*> ruleList;
};

struct WebSite
{
    Node node;
    QString info;
    QString editor;
    QString crawlTime;
    QString threadLimit;
};
#endif // DATAINTERFACE_H
