#include "yzspiderconfigtreeview.h"

YZSpiderConfigTreeView::YZSpiderConfigTreeView(QWidget *parent) :
    QTreeView(parent)
{
    QFileSystemModel *model = new QFileSystemModel;
    model->setRootPath(QDir::currentPath());
    this->setModel(model);
}
