#include "yzspiderruleconfigwidget.h"

YZSpiderRuleConfigWidget::YZSpiderRuleConfigWidget(QWidget *parent) :
    QWidget(parent)
{
    ui.setupUi(this);
}

void YZSpiderRuleConfigWidget::loadRuleItem(Rule *ruleItem)
{
    ui.lineEdit->clear();
    ui.lineEdit->setText(ruleItem->maxPageCount);
}
