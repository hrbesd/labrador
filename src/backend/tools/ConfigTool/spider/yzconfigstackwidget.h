#ifndef YZCONFIGSTACKWIDGET_H
#define YZCONFIGSTACKWIDGET_H

#include <QStackedWidget>
#include "yzspidernodeconfigwidget.h"
#include "yzspiderruleconfigwidget.h"
#include "DataInterface.h"

class YZConfigStackWidget : public QStackedWidget
{
    Q_OBJECT
public:
    explicit YZConfigStackWidget(QWidget *parent = 0);
    
signals:
    
public slots:
    void treeItemDoubleClickedSlot(TreeItem *treeItem);
private:
    void loadNodeConfigWidget(TreeItem *item);
    void loadRuleConfigWidget(TreeItem *item);
    YZSpiderNodeConfigWidget *nodeConfigWidget;
    YZSpiderRuleConfigWidget *ruleConfigWidget;
};

#endif // YZCONFIGSTACKWIDGET_H
