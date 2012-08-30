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
    m_fileMenu = menuBar()->addMenu(tr("&File"));
    m_fileMenu->addAction(m_saveAction);
    m_spiderMenu = menuBar()->addMenu(tr("&Spider"));
    m_spiderMenu->addAction(m_loadAction);
    m_parserMenu = menuBar()->addMenu(tr("&Parser"));
    m_parserMenu->addAction(m_loadParserConfigAction);
}

void YZConfigWindow::createActions()
{
    m_saveAction = new QAction(tr("Save"),this);
    m_loadAction = new QAction(tr("Load Config File"),this);
    m_loadParserConfigAction = new QAction(tr("Load Config File"),this);
    connect(m_saveAction,SIGNAL(triggered()),this,SLOT(saveSpiderConfigFile()));
    connect(m_loadAction,SIGNAL(triggered()),this,SLOT(loadSpiderConfigFile()));
    connect(m_loadParserConfigAction,SIGNAL(triggered()),this,SLOT(loadParserConfigFile()));
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
    m_spiderConfigWidget->saveSpiderConfigFile(m_spiderConfigFileName);
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
    m_parserConfigWidget->saveParserConfigFile(m_parserConfigFileName);
}
