#ifndef YZSPIDERCONFIGTREEVIEW_H
#define YZSPIDERCONFIGTREEVIEW_H

#include <QWidget>
#include <QTreeView>
#include <QFileSystemModel>
#include "spiderconfigmodel.h"

class YZSpiderConfigTreeView : public QTreeView
{
    Q_OBJECT
public:
    explicit YZSpiderConfigTreeView(QWidget *parent = 0);
    
signals:
    
public slots:
    
};

#endif // YZSPIDERCONFIGTREEVIEW_H
