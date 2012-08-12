#ifndef YZSPIDEREXPRESSIONCONFIGWIDGET_H
#define YZSPIDEREXPRESSIONCONFIGWIDGET_H

#include <QWidget>
#include "ui_ExpressionConfig.h"

class YZSpiderExpressionConfigWidget : public QWidget
{
    Q_OBJECT
public:
    explicit YZSpiderExpressionConfigWidget(QWidget *parent = 0);
    
signals:
    
public slots:
private:
    Ui::ExpressionConfig ui;
};

#endif // YZSPIDEREXPRESSIONCONFIGWIDGET_H
