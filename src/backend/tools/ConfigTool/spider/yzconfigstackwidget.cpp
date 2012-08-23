#include "yzconfigstackwidget.h"
#include <QDebug>

YZConfigStackWidget::YZConfigStackWidget(QWidget *parent) :
    QStackedWidget(parent)
{
    nodeConfigWidget = new YZSpiderNodeConfigWidget(this);
    ruleConfigWidget = new YZSpiderRuleConfigWidget(this);
    this->addWidget(nodeConfigWidget);
    this->addWidget(ruleConfigWidget);
    this->setCurrentIndex(1);
}

void YZConfigStackWidget::treeItemDoubleClickedSlot(TreeItem *treeItem)
{
    switch (treeItem->dataItem->itemType) {
    case Item::NODE:
        this->loadNodeConfigWidget(treeItem);
        break;
    case Item::RULE:
        this->loadRuleConfigWidget(treeItem);
        break;
    default:
        break;
    }
}

void YZConfigStackWidget::loadNodeConfigWidget(TreeItem *item)
{
    this->setCurrentIndex(0);
    Node *nodeItem = dynamic_cast<Node*>(item->dataItem);
    nodeConfigWidget->loadNodeItem(nodeItem);
}

void YZConfigStackWidget::loadRuleConfigWidget(TreeItem *item)
{
    this->setCurrentIndex(1);
    Rule *ruleItem = dynamic_cast<Rule*>(item->dataItem);
    ruleConfigWidget->loadRuleItem(ruleItem);
}

void YZConfigStackWidget::save()
{

}

void YZConfigStackWidget::cancel()
{

}


