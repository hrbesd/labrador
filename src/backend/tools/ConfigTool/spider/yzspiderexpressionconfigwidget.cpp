#include "yzspiderexpressionconfigwidget.h"

YZSpiderExpressionConfigWidget::YZSpiderExpressionConfigWidget(Expression &expression, QWidget *parent) :
    QDialog(parent),
    m_expressionItem(expression)
{
    ui.setupUi(this);
    connect(ui.pushButton,SIGNAL(clicked()),this,SLOT(save()));
    connect(ui.pushButton_2,SIGNAL(clicked()),this,SLOT(cancel()));
    loadExpressionItem();
}

void YZSpiderExpressionConfigWidget::save()
{
    m_expressionItem.label = ui.lineEdit->text();
    if(ui.comboBox->currentIndex()==0)
    {
        m_expressionItem.type="RegExp";
    }
    else
    {
        m_expressionItem.type="JavaScript";
    }
    if(ui.comboBox_2->currentIndex()==0)
    {
        m_expressionItem.executeOnlyOnce="true";
    }
    else
    {
        m_expressionItem.executeOnlyOnce="false";
    }
    m_expressionItem.value=ui.plainTextEdit->toPlainText();
}

void YZSpiderExpressionConfigWidget::cancel()
{
    loadExpressionItem();
}

void YZSpiderExpressionConfigWidget::loadExpressionItem()
{
    ui.lineEdit->setText(m_expressionItem.label);
    if(m_expressionItem.label=="Title"||m_expressionItem.label=="Url"||m_expressionItem.label=="NextPage")
    {
        ui.lineEdit->setEnabled(false);
    }
    else
    {
        ui.lineEdit->setEnabled(true);
    }
    if(m_expressionItem.type=="RegExp")
    {
        ui.comboBox->setCurrentIndex(0);
    }
    else
    {
        ui.comboBox->setCurrentIndex(1);
    }
    if(m_expressionItem.executeOnlyOnce=="true")
    {
        ui.comboBox_2->setCurrentIndex(0);
    }
    else
    {
        ui.comboBox_2->setCurrentIndex(1);
    }
    ui.plainTextEdit->setPlainText(m_expressionItem.value);
}
