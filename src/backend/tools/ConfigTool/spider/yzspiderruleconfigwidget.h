#ifndef YZSPIDERRULECONFIGWIDGET_H
#define YZSPIDERRULECONFIGWIDGET_H

#include <QWidget>
#include "DataInterface.h"
#include "ui_RuleConfig.h"

class YZSpiderRuleConfigWidget : public QWidget
{
    Q_OBJECT
public:
    explicit YZSpiderRuleConfigWidget(QWidget *parent = 0);
    
signals:
    
public slots:
private:
    Ui::RuleConfig ui;
};

#endif // YZSPIDERRULECONFIGWIDGET_H
