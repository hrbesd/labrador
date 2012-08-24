#ifndef YZSPIDERRULECONFIGWIDGET_H
#define YZSPIDERRULECONFIGWIDGET_H

#include <QDialog>
#include "DataInterface.h"
#include "ui_RuleConfig.h"

class YZSpiderRuleConfigWidget : public QWidget
{
    Q_OBJECT
public:
    explicit YZSpiderRuleConfigWidget(QWidget *parent = 0,Rule *rule = 0);
    void loadRuleItem(Rule* ruleItem);
signals:
    
public slots:
    void save();
    void cancel();
private slots:
    void loadExpressionItem(const QModelIndex &modelIndex);
    void loadChildRuleItem();
public:
    Ui::RuleConfig ui;
private:
    Expression& getExpressionFromIndex(int index);
    void refreshExpressionList();


    Rule *m_ruleItem;
};

class YZSpiderRuleConfigDialog: public QDialog
{
    Q_OBJECT
public:
    explicit YZSpiderRuleConfigDialog(QWidget *parent = 0,Rule *rule = 0);
};

#endif // YZSPIDERRULECONFIGWIDGET_H
