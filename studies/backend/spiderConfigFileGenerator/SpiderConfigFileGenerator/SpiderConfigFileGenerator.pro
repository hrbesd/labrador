#-------------------------------------------------
#
# Project created by QtCreator 2012-06-12T19:09:35
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = SpiderConfigFileGenerator
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    core/xmlWriter/yzxmlwriter.cpp \
    spiderconfigfilegenerator.cpp

HEADERS += \
    core/xmlWriter/yzxmlwriter.h \
    DataInterface.h \
    spiderconfigfilegenerator.h
