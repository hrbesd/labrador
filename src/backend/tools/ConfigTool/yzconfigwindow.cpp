#include "yzconfigwindow.h"
#include <QDebug>
#include <QTabWidget>

YZConfigWindow::YZConfigWindow(QWidget *parent)
    : QMainWindow(parent)
{
    createActions();
    createMenus();

    tabwidget = new QTabWidget(this);

    m_spiderConfigWidget=new YZSpiderConfigWidget(this);
    tabwidget->addTab(m_spiderConfigWidget,"Spider");
    m_parserConfigWidget = new YZParserConfigWidget(this);
    tabwidget->addTab(m_parserConfigWidget,"Parser");
    this->setCentralWidget(tabwidget);
    this->resize(800,600);
}

YZConfigWindow::~YZConfigWindow()
{
    
}

void YZConfigWindow::createMenus()
{
    m_spiderMenu = menuBar()->addMenu(tr("&Spider"));
    m_spiderMenu->addAction(m_createSpiderConfigAction);
    m_spiderMenu->addAction(m_loadSpiderConfigAction);
    m_spiderMenu->addAction(m_saveSpiderConfigAction);
    m_parserMenu = menuBar()->addMenu(tr("&Parser"));
    m_parserMenu->addAction(m_createParserConfigAction);
    m_parserMenu->addAction(m_loadParserConfigAction);
    m_parserMenu->addAction(m_saveParserConfigAction);
}

void YZConfigWindow::createActions()
{

    m_loadSpiderConfigAction = new QAction(tr("Load Config File"),this);
    m_loadParserConfigAction = new QAction(tr("Load Config File"),this);
    m_saveSpiderConfigAction = new QAction(tr("Save Config File"),this);
    m_saveParserConfigAction = new QAction(tr("Save Config File"),this);
    m_createSpiderConfigAction = new QAction(tr("Create New"),this);
    m_createParserConfigAction = new QAction(tr("Create New"),this);
    connect(m_saveSpiderConfigAction,SIGNAL(triggered()),this,SLOT(saveSpiderConfigFile()));
    connect(m_saveParserConfigAction,SIGNAL(triggered()),this,SLOT(saveParserConfigFile()));
    connect(m_loadSpiderConfigAction,SIGNAL(triggered()),this,SLOT(loadSpiderConfigFile()));
    connect(m_loadParserConfigAction,SIGNAL(triggered()),this,SLOT(loadParserConfigFile()));
    connect(m_createSpiderConfigAction,SIGNAL(triggered()),this,SLOT(createSpiderConfigFile()));
    connect(m_createParserConfigAction,SIGNAL(triggered()),this,SLOT(createParserConfigFile()));
}

void YZConfigWindow::loadSpiderConfigFile()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open Spider Config File"), "~/", tr("Config Files (*.xml);;Any File(*)"));
    if(!fileName.isEmpty())
    {
        m_spiderConfigFileName = fileName;
        m_spiderConfigWidget->loadSpiderConfigFile(fileName);
        this->tabwidget->setCurrentIndex(0);
    }
}

void YZConfigWindow::saveSpiderConfigFile()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Save Spider Config File"), m_spiderConfigFileName, tr("Config Files (*.xml);;Any File(*)"));
    if(!fileName.isEmpty())
    {
        m_spiderConfigWidget->saveSpiderConfigFile(fileName);
    }

}

void YZConfigWindow::loadParserConfigFile()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open Parser Config File"), "~/", tr("Config Files (*.js);;Any File(*)"));
    if(!fileName.isEmpty())
    {
        m_parserConfigFileName = fileName;
        m_parserConfigWidget->loadParserConfigFile(fileName);
        this->tabwidget->setCurrentIndex(1);
    }
}

void YZConfigWindow::saveParserConfigFile()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Save Parser Config File"), m_parserConfigFileName, tr("Config Files (*.js);;Any File(*)"));
    if(!fileName.isEmpty())
    {
        m_parserConfigWidget->saveParserConfigFile(fileName);
    }
}

void YZConfigWindow::createSpiderConfigFile()
{

}

void YZConfigWindow::createParserConfigFile()
{

}
