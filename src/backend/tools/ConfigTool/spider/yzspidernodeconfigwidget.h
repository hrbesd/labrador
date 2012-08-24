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
    explicit YZSpiderNodeConfigWidget(QWidget *parent = 0,Node *node = 0);
    void loadNodeItem(Node* node);
signals:
    
public slots:
    void save();
    void cancel();
private:
    Ui::Form ui;
    Node *m_nodeItem;
};

#endif // YZSPIDERNODECONFIGWIDGET_H
