#include "yzspiderconfigtreeview.h"
#include <QDebug>
#include "DataInterface.h"

YZSpiderConfigTreeView::YZSpiderConfigTreeView(QWidget *parent) :
    QTreeView(parent)
{
    model = new SpiderConfigModel(this);
    this->setModel(model);
    initConnections();
    this->setExpandsOnDoubleClick(false);
}

void YZSpiderConfigTreeView::doubleClickedSlot(const QModelIndex &index)
{
    TreeItem *itemPointer = (TreeItem*)index.internalPointer();
    emit treeItemDoubleClickedSignal(itemPointer);
}

void YZSpiderConfigTreeView::initConnections()
{
    connect(this,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(doubleClickedSlot(QModelIndex)));
}
