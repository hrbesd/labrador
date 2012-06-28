#-------------------------------------------------
#
# Project created by QtCreator 2012-06-05T20:07:08
#
#-------------------------------------------------

QT       += core xml script

QT       -= gui

TARGET = YZParser
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    parser/yzparser.cpp \
    xmlWriter/yzxmlwriter.cpp

HEADERS += \
    parser/yzparser.h \
    DataInterface.h \
    xmlWriter/yzxmlwriter.h
