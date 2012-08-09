#ifndef YZCONFIGWINDOW_H
#define YZCONFIGWINDOW_H

#include <QMainWindow>
#include "yzspiderconfigwidget.h"

class YZConfigWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    YZConfigWindow(QWidget *parent = 0);
    ~YZConfigWindow();
private:
    YZSpiderConfigWidget *m_spiderConfigWidget;
};

#endif // YZCONFIGWINDOW_H
