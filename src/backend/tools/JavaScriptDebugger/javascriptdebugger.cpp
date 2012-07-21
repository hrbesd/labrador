#include "javascriptdebugger.h"

JavaScriptDebugger::JavaScriptDebugger(QWidget *parent)
    : QWidget(parent)
{
    initUI();
    initConnections();
    clear();
}

void JavaScriptDebugger::initUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QHBoxLayout *buttonsLayout = new QHBoxLayout(this);
    QSplitter *mainSplitter = new QSplitter(this);
    mainLayout->addWidget(mainSplitter);
    mainLayout->addLayout(buttonsLayout);

    //buttons
    buttonsLayout->addStretch(5);
    executeButton = new QPushButton(this);
    executeButton->setText("Execute");
    executeButton->setToolTip("execute javascript code");
    executeButton->setFixedSize(100,30);
    clearButton = new QPushButton(this);
    clearButton->setText("Clear");
    clearButton->setToolTip("clear all data");
    clearButton->setFixedSize(100,30);
    buttonsLayout->addWidget(executeButton);
    buttonsLayout->addWidget(clearButton);
    buttonsLayout->addStretch(1);

    //mainSplitter
    contentTextEdit = new QPlainTextEdit(this);
    QSplitter *javascriptSplitter = new QSplitter(this);
    mainSplitter->addWidget(contentTextEdit);
    mainSplitter->addWidget(javascriptSplitter);

    //javascriptSplitter
    javascriptSplitter->setOrientation(Qt::Vertical);
    javascriptTextEdit = new QPlainTextEdit(this);
    QFontMetrics fm(javascriptTextEdit->font());
    javascriptTextEdit->setTabStopWidth(fm.width(' ')*4);
    resultTextEdit = new QPlainTextEdit(this);
    javascriptSplitter->addWidget(javascriptTextEdit);
    javascriptSplitter->addWidget(resultTextEdit);

    this->setLayout(mainLayout);
}

JavaScriptDebugger::~JavaScriptDebugger()
{
    
}

void JavaScriptDebugger::initConnections()
{
    connect(executeButton,SIGNAL(clicked()),this,SLOT(execute()));
    connect(clearButton,SIGNAL(clicked()),this,SLOT(clear()));
}

void JavaScriptDebugger::clear()
{
    contentTextEdit->clear();
    javascriptTextEdit->clear();
    javascriptTextEdit->appendPlainText("function getYZSpiderResult(content)\n"
                                        "{\n"
                                        "    var result = new Array();\n"
                                        "\n"
                                        "    return result;\n"
                                        "}\n");
    resultTextEdit->clear();
}

void JavaScriptDebugger::execute()
{
    int count = 0;
    resultTextEdit->clear();
    QScriptValue result = m_engine.evaluate(javascriptTextEdit->toPlainText());
    if (m_engine.hasUncaughtException()) {
        int line = m_engine.uncaughtExceptionLineNumber();
        resultStringList.clear();
        resultStringList.append(QString("uncaught exception at line")+line+":"+result.toString());
    }
    m_functionValue = m_engine.globalObject().property("getYZSpiderResult");
    QScriptValueList args;
    args << QScriptValue(contentTextEdit->toPlainText());
    QScriptValue resultValue = m_functionValue.call(QScriptValue(),args);
    resultStringList = resultValue.toVariant().toStringList();
    foreach(QString str, resultStringList)
    {
        resultTextEdit->appendPlainText(QString::number(++count) + ":"  + str+"\n");
    }
    m_engine.abortEvaluation();
}
