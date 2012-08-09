#include <QApplication>
#include "yzconfigwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    YZConfigWindow w;
    w.show();
    
    return a.exec();
}
