#ifndef YZCONFIGSTACKWIDGET_H
#define YZCONFIGSTACKWIDGET_H

#include <QStackedWidget>
#include "yzspidernodeconfigwidget.h"
#include "yzspiderruleconfigwidget.h"

class YZConfigStackWidget : public QStackedWidget
{
    Q_OBJECT
public:
    explicit YZConfigStackWidget(QWidget *parent = 0);
    
signals:
    
public slots:
private:
    YZSpiderNodeConfigWidget *nodeConfigWidget;
    YZSpiderRuleConfigWidget *ruleConfigWidget;
};

#endif // YZCONFIGSTACKWIDGET_H
