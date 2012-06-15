#-------------------------------------------------
#
# Project created by QtCreator 2012-06-05T16:36:25
#
#-------------------------------------------------

QT       += core network xml

QT       -= gui

TARGET = YZSpider
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    yzspider.cpp \
    yzlogger.cpp

HEADERS += \
    yzspider.h \
    DataInterface.h \
    yzlogger.h
