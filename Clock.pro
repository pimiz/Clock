#-------------------------------------------------
#
# Project created by QtCreator 2015-02-28T22:02:05
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = Clock
CONFIG   += console
CONFIG   -= app_bundle
INCLUDEPATH +=  /usr/local/include/OGRE \
                /usr/local/include/OGRE/Overlay \
                /usr/include/OIS

TEMPLATE = app


SOURCES += main.cpp \
    BaseApplication.cpp \
    ogreapplication.cpp

HEADERS += \
    BaseApplication.h \
    ogreapplication.h
