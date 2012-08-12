#include "yzconfigstackwidget.h"

YZConfigStackWidget::YZConfigStackWidget(QWidget *parent) :
    QStackedWidget(parent)
{
    nodeConfigWidget = new YZSpiderNodeConfigWidget(this);
    ruleConfigWidget = new YZSpiderRuleConfigWidget(this);
    this->addWidget(nodeConfigWidget);
    this->addWidget(ruleConfigWidget);
    this->setCurrentIndex(1);
}


