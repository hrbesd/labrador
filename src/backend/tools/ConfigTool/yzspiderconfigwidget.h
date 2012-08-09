#ifndef YZSPIDERCONFIGWIDGET_H
#define YZSPIDERCONFIGWIDGET_H

#include <QWidget>
#include "yzspiderconfigtreeview.h"
#include <QHBoxLayout>
#include <QVBoxLayout>

class YZSpiderConfigWidget : public QWidget
{
    Q_OBJECT
public:
    explicit YZSpiderConfigWidget(QWidget *parent = 0);

signals:

public slots:
    void loadSpiderConfigFile(QString fileName);
private slots:

private:
    void initConnections();

    YZSpiderConfigTreeView* m_spiderConfigTreeView;
};

#endif // YZSPIDERCONFIGWIDGET_H
