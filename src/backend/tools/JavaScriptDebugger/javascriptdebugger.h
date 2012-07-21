#ifndef JAVASCRIPTDEBUGGER_H
#define JAVASCRIPTDEBUGGER_H

#include <QWidget>
#include <QPlainTextEdit>
#include <QListView>
#include <QSplitter>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QtScript>
#include <QStringListModel>
#include <QFontMetrics>

class JavaScriptDebugger : public QWidget
{
    Q_OBJECT
    
public:
    JavaScriptDebugger(QWidget *parent = 0);
    ~JavaScriptDebugger();
private slots:
    void execute();
    void clear();
    void generate();
private:
    void initUI();
    void initConnections();

    QPushButton *executeButton;
    QPushButton *clearButton;
    QPushButton *generateButton;
    QPlainTextEdit *contentTextEdit;
    QPlainTextEdit *javascriptTextEdit;
    QPlainTextEdit *resultTextEdit;
    QStringList resultStringList;

    QScriptEngine m_engine;
    QScriptValue m_functionValue;
};

#endif // JAVASCRIPTDEBUGGER_H
