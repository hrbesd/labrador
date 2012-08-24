#ifndef YZSPIDEREXPRESSIONCONFIGWIDGET_H
#define YZSPIDEREXPRESSIONCONFIGWIDGET_H

#include <QDialog>
#include "DataInterface.h"
#include "ui_ExpressionConfig.h"

class YZSpiderExpressionConfigWidget : public QDialog
{
    Q_OBJECT
public:
    explicit YZSpiderExpressionConfigWidget(Expression& expression, QWidget *parent = 0);
    void loadExpressionItem();
signals:
    
public slots:
    void save();
    void cancel();
private:


    Ui::ExpressionConfig ui;
    Expression &m_expressionItem;
};

#endif // YZSPIDEREXPRESSIONCONFIGWIDGET_H
