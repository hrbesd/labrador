#include <QApplication>
#include "javascriptdebugger.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    JavaScriptDebugger w;
    w.show();
    
    return a.exec();
}
