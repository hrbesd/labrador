#ifndef SPIDERCONFIGMODEL_H
#define SPIDERCONFIGMODEL_H

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>
#include "DataInterface.h"

class SpiderConfigModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit SpiderConfigModel(QObject *parent = 0);
    
//    QVariant data(const QModelIndex &index, int role) const;
//    Qt::ItemFlags flags(const QModelIndex &index) const;
//    QVariant headerData(int section, Qt::Orientation orientation,
//                        int role = Qt::DisplayRole) const;
//    QModelIndex index(int row, int column,
//                      const QModelIndex &parent = QModelIndex()) const;
//    QModelIndex parent(const QModelIndex &index) const;
//    int rowCount(const QModelIndex &parent = QModelIndex()) const;
//    int columnCount(const QModelIndex &parent = QModelIndex()) const;
signals:
    
public slots:
private:
    WebSite m_website;
};

#endif // SPIDERCONFIGMODEL_H
