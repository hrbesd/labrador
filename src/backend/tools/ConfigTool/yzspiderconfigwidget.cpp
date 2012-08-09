#include "yzspiderconfigwidget.h"

YZSpiderConfigWidget::YZSpiderConfigWidget(QWidget *parent) :
    QWidget(parent)
{
    m_spiderConfigTreeView = new YZSpiderConfigTreeView(this);
    QVBoxLayout *vboxLayout = new QVBoxLayout(this);
    vboxLayout->addWidget(m_spiderConfigTreeView);
    this->setLayout(vboxLayout);

    initConnections();
}

void YZSpiderConfigWidget::initConnections()
{

}

void YZSpiderConfigWidget::loadSpiderConfigFile(QString fileName)
{
    m_spiderConfigTreeView->model->loadConfigFile(fileName);
}
