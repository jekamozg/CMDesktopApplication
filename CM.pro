#-------------------------------------------------
#
# Project created by QtCreator 2012-07-08T22:11:39
#
#-------------------------------------------------

QT       += core gui network

TARGET = CM
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    loginwindow.cpp \
    httpmanager.cpp \
    qt-json/json.cpp

HEADERS  += mainwindow.h \
    loginwindow.h \
    httpmanager.h \
    qt-json/json.h

FORMS    += mainwindow.ui \
    loginwindow.ui
