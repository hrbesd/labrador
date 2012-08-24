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
    this->setContextMenuPolicy(Qt::ActionsContextMenu);
    addChildAction = new QAction("append child",this);
    deleteAction = new QAction("delete",this);
    this->addAction(addChildAction);
    this->addAction(deleteAction);
    connect(addChildAction,SIGNAL(triggered()),this,SLOT(addChildSlot()));
    connect(deleteAction,SIGNAL(triggered()),this,SLOT(deleteSlot()));
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

void YZSpiderConfigTreeView::addChildSlot()
{
    this->model->insertRows(0,1,this->currentIndex());
}

void YZSpiderConfigTreeView::deleteSlot()
{
    TreeItem *treeItem = (TreeItem*)this->currentIndex().internalPointer();
    this->model->removeRows(treeItem->childNumber(),1,this->currentIndex().parent());
}


