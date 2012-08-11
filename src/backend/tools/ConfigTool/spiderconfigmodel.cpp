#include "spiderconfigmodel.h"
#include <QDebug>

SpiderConfigModel::SpiderConfigModel(QObject *parent) :
    QAbstractItemModel(parent)
{
    rootItem = new TreeItem(0,0);
}

SpiderConfigModel::~SpiderConfigModel()
{
    delete rootItem;
}

int SpiderConfigModel::columnCount(const QModelIndex & /* parent */) const
{
    return 1;
}

QVariant SpiderConfigModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole && role != Qt::EditRole)
        return QVariant();

    TreeItem *item = getItem(index);

    return item->data(index.column());
}

Qt::ItemFlags SpiderConfigModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

    return Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

TreeItem *SpiderConfigModel::getItem(const QModelIndex &index) const
{
    if (index.isValid()) {
        TreeItem *item = (TreeItem*)(index.internalPointer());
        if (item) return item;
    }
    return rootItem;
}

QVariant SpiderConfigModel::headerData(int section, Qt::Orientation orientation,
                                       int role) const
{
    return QVariant();
}

QModelIndex SpiderConfigModel::index(int row, int column, const QModelIndex &parent) const
{
    if (parent.isValid() && parent.column() != 0)
        return QModelIndex();

    TreeItem *parentItem = getItem(parent);

    TreeItem *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}
//! [6]

bool SpiderConfigModel::insertColumns(int position, int columns, const QModelIndex &parent)
{

    return true;
}

bool SpiderConfigModel::insertRows(int position, int rows, const QModelIndex &parent)
{
    TreeItem *parentItem = getItem(parent);
    bool success;

    beginInsertRows(parent, position, position + rows - 1);
    success = parentItem->insertChildren(position, rows, rootItem->columnCount());
    endInsertRows();

    return success;
}

QModelIndex SpiderConfigModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    TreeItem *childItem = getItem(index);
    TreeItem *parentItem = childItem->parent();

    if (parentItem == rootItem)
        return QModelIndex();

    return createIndex(parentItem->childNumber(), 0, parentItem);
}
//! [7]

bool SpiderConfigModel::removeColumns(int position, int columns, const QModelIndex &parent)
{
    return true;
}

bool SpiderConfigModel::removeRows(int position, int rows, const QModelIndex &parent)
{
    TreeItem *parentItem = getItem(parent);
    bool success = true;

    beginRemoveRows(parent, position, position + rows - 1);
    success = parentItem->removeChildren(position, rows);
    endRemoveRows();

    return success;
}

int SpiderConfigModel::rowCount(const QModelIndex &parent) const
{
    TreeItem *parentItem = getItem(parent);

    return parentItem->childCount();
}

bool SpiderConfigModel::setData(const QModelIndex &index, const QVariant &value,
                                int role)
{
    if (role != Qt::EditRole)
        return false;

    TreeItem *item = getItem(index);
    bool result = item->setData(index.column(), value);

    if (result)
        emit dataChanged(index, index);

    return result;
}

bool SpiderConfigModel::setHeaderData(int section, Qt::Orientation orientation,
                                      const QVariant &value, int role)
{
    return false;
}

void SpiderConfigModel::loadConfigFile(QString fileName)
{
    YZSpiderConfigFileParser parser;
    parser.parseWebsiteConfigFile(fileName,m_website);
    refreshModelWithWebsiteData();
}

void SpiderConfigModel::refreshModelWithWebsiteData()
{
    this->beginResetModel();
    delete rootItem;
    rootItem = new TreeItem(0,0);
    parseNode(rootItem,&(m_website.node));
    this->endResetModel();
}

void SpiderConfigModel::parseNode(TreeItem *parentTreeItem, Node *nodeItem)
{
    if(nodeItem!=NULL)
    {
        TreeItem *newTreeItem = new TreeItem(parentTreeItem,nodeItem);
        parentTreeItem->appendChild(newTreeItem);
        for(int i=0;i<nodeItem->ruleList.size();i++)
        {
            parseRule(newTreeItem,nodeItem->ruleList[i]);
        }
    }
}

void SpiderConfigModel::parseRule(TreeItem *parentTreeItem, Rule *ruleItem)
{
    if(ruleItem!=NULL)
    {
        TreeItem *newTreeItem = new TreeItem(parentTreeItem,ruleItem);
        parentTreeItem->appendChild(newTreeItem);
        for(int i=0;i<ruleItem->nodeList.size();i++)
        {
            parseNode(newTreeItem,ruleItem->nodeList[i]);
        }
    }
}
