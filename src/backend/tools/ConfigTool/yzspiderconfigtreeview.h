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
    SpiderConfigModel *model;
signals:
    
public slots:
private slots:
    void doubleClickedSlot( const QModelIndex & index );
private:
    void initConnections();
};

#endif // YZSPIDERCONFIGTREEVIEW_H
