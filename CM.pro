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
    log.cpp \
    tasksform.cpp \
    popuptaskform.cpp \
    taskformwidget.cpp

HEADERS  += mainwindow.h \
    loginwindow.h \
    httpmanager.h \
    qt-json/json.h \
    log.h \
    tasksform.h \
    popuptaskform.h \
    taskformwidget.h

FORMS    += mainwindow.ui \
    loginwindow.ui \
    tasksform.ui \
    popuptaskform.ui \
    taskformwidget.ui

RESOURCES += \
    css.qrc
