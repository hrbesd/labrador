#-------------------------------------------------
#
# Project created by QtCreator 2012-08-04T17:26:50
#
#-------------------------------------------------

QT       += core gui script

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ConfigTool
TEMPLATE = app


SOURCES += main.cpp\
        yzconfigwindow.cpp \
    yzspiderconfigwidget.cpp \
    yzspiderconfigtreeview.cpp \
    spiderconfigmodel.cpp \
    DataInterface.cpp \
    spider/yzspiderconfigfileparser.cpp \
    spider/yzspidernodeconfigwidget.cpp \
    spider/yzspiderruleconfigwidget.cpp \
    spider/yzconfigstackwidget.cpp \
    spider/yzspiderexpressionconfigwidget.cpp \
    spider/yzxmlwriter.cpp \
    parser/yzparserconfigwidget.cpp

HEADERS  += yzconfigwindow.h \
    yzspiderconfigwidget.h \
    yzspiderconfigtreeview.h \
    DataInterface.h \
    spiderconfigmodel.h \
    spider/yzspiderconfigfileparser.h \
    spider/yzspidernodeconfigwidget.h \
    spider/yzspiderruleconfigwidget.h \
    spider/yzconfigstackwidget.h \
    spider/yzspiderexpressionconfigwidget.h \
    spider/yzxmlwriter.h \
    parser/yzparserconfigwidget.h

FORMS += \
    spider/NodeConfigWidget.ui \
    spider/RuleConfig.ui \
    spider/ExpressionConfig.ui \
    parser/parserConfigWidget.ui \
    parser/parserTargetWidget.ui \
    parser/parserResultWidget.ui \
    spider/Website.ui
