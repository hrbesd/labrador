#ifndef YZCONFIGWINDOW_H
#define YZCONFIGWINDOW_H

#include <QMainWindow>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QFileDialog>
#include "yzspiderconfigwidget.h"

class YZConfigWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    YZConfigWindow(QWidget *parent = 0);
    ~YZConfigWindow();

private slots:
    void loadSpiderConfigFile();
private:
    void createActions();
    void createMenus();

    QMenu* m_spiderMenu;
    QAction *m_loadAction;

    YZSpiderConfigWidget *m_spiderConfigWidget;
};

#endif // YZCONFIGWINDOW_H
