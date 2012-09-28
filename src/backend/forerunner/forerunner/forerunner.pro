#-------------------------------------------------
#
# Project created by QtCreator 2012-09-28T16:02:38
#
#-------------------------------------------------

QT       += core network xml script

QT       -= gui

TARGET = forerunner
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    forerunner.cpp \
    yzspiderconfigfileparser.cpp \
    yzlogger.cpp \
    core/xmlWriter/yzxmlwriter.cpp

HEADERS += \
    forerunner.h \
    yzspiderconfigfileparser.h \
    yzlogger.h \
    version.h \
    core/xmlWriter/yzxmlwriter.h \
    DataInterface.h
