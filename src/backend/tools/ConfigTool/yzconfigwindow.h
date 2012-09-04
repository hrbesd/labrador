#ifndef YZCONFIGWINDOW_H
#define YZCONFIGWINDOW_H

#include <QMainWindow>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QFileDialog>
#include "yzspiderconfigwidget.h"
#include "parser/yzparserconfigwidget.h"

class YZConfigWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    YZConfigWindow(QWidget *parent = 0);
    ~YZConfigWindow();

private slots:
    void loadSpiderConfigFile();
    void saveSpiderConfigFile();
    void loadParserConfigFile();
    void saveParserConfigFile();
    void createSpiderConfigFile();
    void createParserConfigFile();
private:
    void createActions();
    void createMenus();
    //menus and actions

    QMenu* m_spiderMenu;
    QAction *m_loadSpiderConfigAction;
    QAction *m_saveSpiderConfigAction;
    QAction *m_createSpiderConfigAction;

    QMenu* m_parserMenu;
    QAction *m_loadParserConfigAction;
    QAction *m_saveParserConfigAction;
    QAction *m_createParserConfigAction;
    //properties
    QString m_spiderConfigFileName;
    QString m_parserConfigFileName;

    YZSpiderConfigWidget *m_spiderConfigWidget;
    YZParserConfigWidget *m_parserConfigWidget;
    QTabWidget *tabwidget;
};

#endif // YZCONFIGWINDOW_H
