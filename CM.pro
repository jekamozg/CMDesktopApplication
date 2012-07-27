#-------------------------------------------------
#
# Project created by QtCreator 2012-07-08T22:11:39
#
#-------------------------------------------------

QT       += core gui network sql

TARGET = CM
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    loginwindow.cpp \
    httpmanager.cpp \
    qt-json/json.cpp \
    log.cpp

HEADERS  += mainwindow.h \
    loginwindow.h \
    httpmanager.h \
    qt-json/json.h \
    log.h

FORMS    += mainwindow.ui \
    loginwindow.ui
