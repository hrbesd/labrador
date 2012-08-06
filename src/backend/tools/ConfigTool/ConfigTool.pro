#-------------------------------------------------
#
# Project created by QtCreator 2012-08-04T17:26:50
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ConfigTool
TEMPLATE = app


SOURCES += main.cpp\
        yzconfigwindow.cpp \
    yzspiderconfigwidget.cpp \
    yzspiderconfigtreeview.cpp \
    spiderconfigmodel.cpp \
    DataInterface.cpp

HEADERS  += yzconfigwindow.h \
    yzspiderconfigwidget.h \
    yzspiderconfigtreeview.h \
    DataInterface.h \
    spiderconfigmodel.h
