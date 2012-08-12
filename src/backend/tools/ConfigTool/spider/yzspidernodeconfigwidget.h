#ifndef YZSPIDERNODECONFIGWIDGET_H
#define YZSPIDERNODECONFIGWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLayout>
#include "DataInterface.h"
#include "ui_NodeConfigWidget.h"

class YZSpiderNodeConfigWidget : public QWidget
{
    Q_OBJECT
public:
    explicit YZSpiderNodeConfigWidget(QWidget *parent = 0);
    void show(Node *node);
signals:
    
public slots:
    void save();
    void cancel();
private:
    Ui::Form ui;

};

#endif // YZSPIDERNODECONFIGWIDGET_H
