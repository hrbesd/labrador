#-------------------------------------------------
#
# Project created by QtCreator 2012-07-12T15:35:17
#
#-------------------------------------------------

QT       += core xml

QT       -= gui

TARGET = producer
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    generator.cpp \
    yzlogger.cpp

HEADERS += \
    generator.h \
    version.h \
    DataInterface.h \
    yzlogger.h
