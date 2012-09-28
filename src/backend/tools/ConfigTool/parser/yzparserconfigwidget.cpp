#include "yzparserconfigwidget.h"
#include <QString>

YZParserConfigWidget::YZParserConfigWidget(QWidget *parent) :
    QWidget(parent)
{
    initUI();
    initConnections();
}

void YZParserConfigWidget::loadParserConfigFile(QString fileName)
{
    QString configFile = fileName;
    QFile file(configFile);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qWarning("can't open config File");
        exit(0);
    }
    configUi.plainTextEdit->setPlainText(QString(file.readAll()));
}

void YZParserConfigWidget::saveParserConfigFile(QString fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qWarning()<<"can't open file";
        return;
    }
    QTextStream out(&file);
    out<<configUi.plainTextEdit->toPlainText();
    out.flush();
    file.close();
}

void YZParserConfigWidget::initUI()
{
    configWidget = new QWidget(this);
    resultWidget = new QWidget(this);
    targetWidget = new QWidget(this);
    configUi.setupUi(configWidget);
    resultUi.setupUi(resultWidget);
    targetUi.setupUi(targetWidget);

    QSplitter *splitter1 = new QSplitter(this);
    splitter1->setLayoutDirection(Qt::LeftToRight);
    splitter1->addWidget(configWidget);
    splitter1->addWidget(targetWidget);
    QSplitter *splitter2 = new QSplitter(this);
    QSizePolicy policy;
    policy.setVerticalStretch(2);
    splitter2->setOrientation(Qt::Vertical);
    splitter2->addWidget(splitter1);
    splitter2->widget(0)->setSizePolicy(policy);
    splitter2->addWidget(resultWidget);
    policy.setVerticalStretch(1);
    splitter2->widget(1)->setSizePolicy(policy);
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(splitter2);
}

void YZParserConfigWidget::initConnections()
{
    connect(resultUi.pushButton,SIGNAL(clicked()),this,SLOT(execute()));
    connect(resultUi.pushButton_2,SIGNAL(clicked()),this,SLOT(clear()));
}

void YZParserConfigWidget::execute()
{
    this->clear();
    QScriptValue result = m_engine.evaluate(configUi.plainTextEdit->toPlainText());
    m_functionValue = m_engine.globalObject().property("parseArticle");
    QScriptValueList args;
    QString str(targetUi.plainTextEdit->toPlainText());
    QString str2(targetUi.lineEdit->text());
    args << QScriptValue(str)<<QScriptValue(str2);
    QScriptValue article = m_functionValue.call(QScriptValue(),args);
    QVariant articleItem = article.toVariant();

    resultUi.plainTextEdit->appendPlainText(QString("version:")  + QString::fromUtf8(articleItem.toMap()["version"].toByteArray().data())+"\n");
    resultUi.plainTextEdit->appendPlainText(QString("lastModified:")  + QString::fromUtf8(articleItem.toMap()["lastModified"].toByteArray().data())+"\n");
    resultUi.plainTextEdit->appendPlainText(QString("refreshTag:")  + QString::fromUtf8(articleItem.toMap()["refreshTag"].toByteArray().data())+"\n");
    resultUi.plainTextEdit->appendPlainText(QString("author:")  + QString::fromUtf8(articleItem.toMap()["author"].toByteArray().data())+"\n");
    resultUi.plainTextEdit->appendPlainText(QString("body:")  + QString::fromUtf8(articleItem.toMap()["body"].toByteArray().data())+"\n");
}

void YZParserConfigWidget::clear()
{
    resultUi.plainTextEdit->clear();
}
