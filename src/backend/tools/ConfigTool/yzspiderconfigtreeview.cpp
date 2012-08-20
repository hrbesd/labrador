#include "yzspiderconfigtreeview.h"
#include <QDebug>

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
    qDebug()<<index;
}

void YZSpiderConfigTreeView::initConnections()
{
    connect(this,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(doubleClickedSlot(QModelIndex)));
}
