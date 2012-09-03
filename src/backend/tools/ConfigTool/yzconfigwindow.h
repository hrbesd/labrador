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
private:
    void createActions();
    void createMenus();
    //menus and actions
    QMenu* m_fileMenu;
    QAction* m_saveAction;

    QMenu* m_spiderMenu;
    QAction *m_loadAction;

    QMenu* m_parserMenu;
    QAction *m_loadParserConfigAction;

    //properties
    QString m_spiderConfigFileName;
    QString m_parserConfigFileName;

    YZSpiderConfigWidget *m_spiderConfigWidget;
    YZParserConfigWidget *m_parserConfigWidget;
    QTabWidget *tabwidget;
};

#endif // YZCONFIGWINDOW_H
