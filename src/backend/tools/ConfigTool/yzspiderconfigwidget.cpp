#include "yzspiderconfigwidget.h"

YZSpiderConfigWidget::YZSpiderConfigWidget(QWidget *parent) :
    QWidget(parent)
{
    m_spiderConfigTreeView = new YZSpiderConfigTreeView(this);
    QVBoxLayout *vboxLayout = new QVBoxLayout(this);
    QSplitter *splitter = new QSplitter(this);
    splitter->setLayoutDirection(Qt::LeftToRight);
    splitter->addWidget(m_spiderConfigTreeView);
    m_configStackWidget = new YZConfigStackWidget(this);
    splitter->addWidget(m_configStackWidget);
    vboxLayout->addWidget(splitter);
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
