#ifndef YZPARSERCONFIGWIDGET_H
#define YZPARSERCONFIGWIDGET_H

#include <QWidget>
#include <QSplitter>
#include "ui_parserConfigWidget.h"
#include "ui_parserResultWidget.h"
#include "ui_parserTargetWidget.h"
#include <QtScript>

class YZParserConfigWidget : public QWidget
{
    Q_OBJECT
public:
    explicit YZParserConfigWidget(QWidget *parent = 0);
    
signals:
    
public slots:
    void loadParserConfigFile(QString fileName);
    void saveParserConfigFile(QString fileName);
private slots:
    void execute();
    void clear();
private:
    void initUI();
    void initConnections();

    Ui::ParserTarget targetUi;
    Ui::ParserConfig configUi;
    Ui::ParserResult resultUi;

    QWidget *targetWidget;
    QWidget *configWidget;
    QWidget *resultWidget;

    QScriptEngine m_engine;
    QScriptValue m_functionValue;
};

#endif // YZPARSERCONFIGWIDGET_H
