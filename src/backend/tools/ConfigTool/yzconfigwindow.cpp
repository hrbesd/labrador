#include "yzconfigwindow.h"

YZConfigWindow::YZConfigWindow(QWidget *parent)
    : QMainWindow(parent)
{
    m_spiderConfigWidget=new YZSpiderConfigWidget(this);
    this->setCentralWidget(m_spiderConfigWidget);
    this->resize(800,600);
}

YZConfigWindow::~YZConfigWindow()
{
    
}
