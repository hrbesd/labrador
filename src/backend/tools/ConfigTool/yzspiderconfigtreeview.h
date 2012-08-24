#ifndef YZSPIDERCONFIGTREEVIEW_H
#define YZSPIDERCONFIGTREEVIEW_H

#include <QWidget>
#include <QTreeView>
#include <QFileSystemModel>
#include "spiderconfigmodel.h"
#include "DataInterface.h"
#include <QAction>

class YZSpiderConfigTreeView : public QTreeView
{
    Q_OBJECT
public:
    explicit YZSpiderConfigTreeView(QWidget *parent = 0);
    SpiderConfigModel *model;
signals:
    void treeItemDoubleClickedSignal(TreeItem* treeItem);
public slots:
private slots:
    void doubleClickedSlot( const QModelIndex & index );
    void addChildSlot();
    void deleteSlot();
private:
    void initConnections();
    QAction *addChildAction;
    QAction *deleteAction;
};

#endif // YZSPIDERCONFIGTREEVIEW_H
