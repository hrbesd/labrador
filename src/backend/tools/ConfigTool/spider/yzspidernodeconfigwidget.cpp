#include "yzspidernodeconfigwidget.h"
#include <QDebug>

YZSpiderNodeConfigWidget::YZSpiderNodeConfigWidget(QWidget *parent) :
    QWidget(parent)
{
    ui.setupUi(this);
}

void YZSpiderNodeConfigWidget::save()
{

}

void YZSpiderNodeConfigWidget::cancel()
{

}

void YZSpiderNodeConfigWidget::loadNodeItem(Node *node)
{
    ui.lineEdit->clear();
    ui.lineEdit_2->clear();
    ui.lineEdit_3->clear();
    ui.lineEdit->setText(node->name);
    ui.lineEdit_2->setText(node->url);
    ui.lineEdit_3->setText(node->refreshRate);
}
