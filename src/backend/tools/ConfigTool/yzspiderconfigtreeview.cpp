#include "yzspiderconfigtreeview.h"

YZSpiderConfigTreeView::YZSpiderConfigTreeView(QWidget *parent) :
    QTreeView(parent)
{
    SpiderConfigModel *model = new SpiderConfigModel(this);
    this->setModel(model);
}
