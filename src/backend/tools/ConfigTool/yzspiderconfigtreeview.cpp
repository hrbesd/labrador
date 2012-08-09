#include "yzspiderconfigtreeview.h"

YZSpiderConfigTreeView::YZSpiderConfigTreeView(QWidget *parent) :
    QTreeView(parent)
{
    model = new SpiderConfigModel(this);
    this->setModel(model);
}
