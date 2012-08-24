#include "yzspiderruleconfigwidget.h"
#include <QDebug>
#include "yzspiderexpressionconfigwidget.h"
YZSpiderRuleConfigWidget::YZSpiderRuleConfigWidget(QWidget *parent, Rule *rule) :
    QWidget(parent)
{
    ui.setupUi(this);
    loadRuleItem(rule);
    connect(ui.pushButton_4,SIGNAL(clicked()),this,SLOT(save()));
    connect(ui.pushButton_5,SIGNAL(clicked()),this,SLOT(cancel()));
    connect(ui.listWidget,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(loadExpressionItem(QModelIndex)));
    connect(ui.pushButton,SIGNAL(clicked()),this,SLOT(loadChildRuleItem()));

}

void YZSpiderRuleConfigWidget::loadRuleItem(Rule *ruleItem)
{
    if(ruleItem)
    {
        ui.frame->setEnabled(true);
        m_ruleItem = ruleItem;
        ui.lineEdit->clear();
        ui.lineEdit->setText(ruleItem->maxPageCount);
        refreshExpressionList();
        if(m_ruleItem&&m_ruleItem->childRule)
        {
            ui.pushButton->setEnabled(true);
        }
        else
        {
            ui.pushButton->setEnabled(false);
        }
    }
    else
    {
        ui.frame->setEnabled(false);
    }
}

void YZSpiderRuleConfigWidget::save()
{
    m_ruleItem->maxPageCount=ui.lineEdit->text();
}

void YZSpiderRuleConfigWidget::cancel()
{
    loadRuleItem(m_ruleItem);
}

Expression& YZSpiderRuleConfigWidget::getExpressionFromIndex(int index)
{
    if(index==0)
        return m_ruleItem->titleExpression;
    else if(index==1)
        return m_ruleItem->urlExpression;
    else if(index==2)
        return m_ruleItem->nextPageExpression;
    else
        return m_ruleItem->expressionList[index-3];
}

void YZSpiderRuleConfigWidget::refreshExpressionList()
{
    ui.listWidget->clear();
    ui.listWidget->addItem("Title");
    ui.listWidget->addItem("Url");
    ui.listWidget->addItem("NextPage");
    for(int i=0;i<m_ruleItem->expressionList.size();i++)
    {
        ui.listWidget->addItem(m_ruleItem->expressionList[i].label);
    }
}

void YZSpiderRuleConfigWidget::loadExpressionItem(const QModelIndex &modelIndex)
{
    if(m_ruleItem)
    {
        YZSpiderExpressionConfigWidget configWidget(getExpressionFromIndex(modelIndex.row()),this);
        configWidget.exec();
    }
}

void YZSpiderRuleConfigWidget::loadChildRuleItem()
{
    YZSpiderRuleConfigDialog configDialog(0,m_ruleItem->childRule);
    configDialog.exec();
}

YZSpiderRuleConfigDialog::YZSpiderRuleConfigDialog(QWidget *parent, Rule *rule):
    QDialog(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    YZSpiderRuleConfigWidget *widget = new YZSpiderRuleConfigWidget(this,rule);
    widget->ui.pushButton->setEnabled(false);
    layout->addWidget(widget);
    this->setLayout(layout);
}
