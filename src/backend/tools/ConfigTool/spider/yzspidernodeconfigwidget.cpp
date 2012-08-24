#include "yzspidernodeconfigwidget.h"
#include <QDebug>

YZSpiderNodeConfigWidget::YZSpiderNodeConfigWidget(QWidget *parent, Node *node) :
    QWidget(parent),
    m_nodeItem(node)
{
    ui.setupUi(this);
    connect(ui.pushButton,SIGNAL(clicked()),this,SLOT(save()));
    connect(ui.pushButton_2,SIGNAL(clicked()),this,SLOT(cancel()));
}

void YZSpiderNodeConfigWidget::save()
{
    if(m_nodeItem)
    {
        m_nodeItem->name=ui.lineEdit->text();
        m_nodeItem->url=ui.lineEdit_2->text();
        m_nodeItem->refreshRate=ui.lineEdit_3->text();
    }
}

void YZSpiderNodeConfigWidget::cancel()
{
    loadNodeItem(m_nodeItem);
}

void YZSpiderNodeConfigWidget::loadNodeItem(Node *node)
{
    m_nodeItem = node;
    ui.lineEdit->clear();
    ui.lineEdit_2->clear();
    ui.lineEdit_3->clear();
    ui.lineEdit->setText(node->name);
    ui.lineEdit_2->setText(node->url);
    ui.lineEdit_3->setText(node->refreshRate);
}
