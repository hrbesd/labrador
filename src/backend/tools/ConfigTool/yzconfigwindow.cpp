#include "yzconfigwindow.h"
#include <QDebug>

YZConfigWindow::YZConfigWindow(QWidget *parent)
    : QMainWindow(parent)
{
    createActions();
    createMenus();

    m_spiderConfigWidget=new YZSpiderConfigWidget(this);
    this->setCentralWidget(m_spiderConfigWidget);
    this->resize(800,600);
}

YZConfigWindow::~YZConfigWindow()
{
    
}

void YZConfigWindow::createMenus()
{
    m_spiderMenu = menuBar()->addMenu(tr("&Spider"));
    m_spiderMenu->addAction(m_loadAction);
}

void YZConfigWindow::createActions()
{
    m_loadAction = new QAction(tr("Load Config File"),this);
    connect(m_loadAction,SIGNAL(triggered()),this,SLOT(loadSpiderConfigFile()));
}

void YZConfigWindow::loadSpiderConfigFile()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open Spider Config File"), "~/", tr("Config Files (*.xml);;Any File(*)"));
    if(!fileName.isEmpty())
    {
        m_spiderConfigWidget->loadSpiderConfigFile(fileName);
    }
}
