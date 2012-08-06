#ifndef DATAINTERFACE_H
#define DATAINTERFACE_H
#include <QString>
#include <QList>
#include <QVariant>
struct Node;

class TreeItem
{
public:
    TreeItem(TreeItem *parent = 0)
    {
        parentItem = parent;
    }

    virtual TreeItem *child(int number) = 0;
    virtual int childCount() const = 0;
    virtual int columnCount() const = 0;
    virtual QVariant data(int column) const = 0;
    virtual bool insertChildren(int position, int count, int columns) = 0;
    virtual bool insertColumns(int position, int columns) = 0;
    TreeItem *parent()
    {
        return parentItem;
    }
    virtual bool removeChildren(int position, int count) = 0;
    virtual bool removeColumns(int position, int columns) = 0;
    virtual int childNumber() const = 0;
    virtual bool setData(int column, const QVariant &value) = 0;
    TreeItem *parentItem;
};

struct Expression
{
    Expression(QString labelPara = "",QString valuePara = "") {
        type = "RegExp";
        executeOnlyOnce = "false";
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

class Rule : public TreeItem
{
public:
    Rule(TreeItem *parent = 0) : TreeItem(parent) {

        childRule=NULL;
        nextPageExpression.label = "nextPage";
        urlExpression.label = "url";
        titleExpression.label = "title";
    }
    virtual TreeItem *child(int number);
    virtual int childCount() const;
    virtual int columnCount() const;
    virtual QVariant data(int column) const;
    virtual bool insertChildren(int position, int count, int columns);
    virtual bool insertColumns(int position, int columns);
    virtual bool removeChildren(int position, int count);
    virtual bool removeColumns(int position, int columns);
    virtual int childNumber() const;
    virtual bool setData(int column, const QVariant &value);
    QList<Expression*> expressionList;
    Expression nextPageExpression;
    Expression urlExpression;
    Expression titleExpression;
    QString maxPageCount;
    QList<Node*> nodeList;
    Rule* childRule;
    ~Rule(){
        delete childRule;
        qDeleteAll(nodeList);
        qDeleteAll(expressionList);
    }
};

class Node : public TreeItem
{
public:
    Node(TreeItem *parent = 0);
    virtual TreeItem *child(int number);
    virtual int childCount() const;
    virtual int columnCount() const;
    virtual QVariant data(int column) const;
    virtual bool insertChildren(int position, int count, int columns);
    virtual bool insertColumns(int position, int columns);
    virtual bool removeChildren(int position, int count);
    virtual bool removeColumns(int position, int columns);
    virtual int childNumber() const;
    virtual bool setData(int column, const QVariant &value);
    QString url;
    QString name;
    QString refreshRate;
    QList<Rule*> ruleList;
    ~Node(){
        qDeleteAll(ruleList);
    }
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
