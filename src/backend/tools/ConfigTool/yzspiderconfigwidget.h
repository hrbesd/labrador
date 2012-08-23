#ifndef YZSPIDERCONFIGWIDGET_H
#define YZSPIDERCONFIGWIDGET_H

#include <QWidget>
#include "yzspiderconfigtreeview.h"
#include "spider/yzconfigstackwidget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QSpacerItem>
#include <QSplitter>

class YZSpiderConfigWidget : public QWidget
{
    Q_OBJECT
public:
    explicit YZSpiderConfigWidget(QWidget *parent = 0);

signals:

public slots:
    void loadSpiderConfigFile(QString fileName);
    void saveSpiderConfigFile(QString fileName);
private slots:

private:
    void initConnections();

    YZSpiderConfigTreeView* m_spiderConfigTreeView;
    YZConfigStackWidget *m_configStackWidget;

};

#endif // YZSPIDERCONFIGWIDGET_H
