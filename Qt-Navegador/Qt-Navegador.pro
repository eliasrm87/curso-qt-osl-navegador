#-------------------------------------------------
#
# Project created by QtCreator 2014-02-11T17:47:37
#
#-------------------------------------------------

QT       += core gui webkitwidgets network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Qt-Navegador-exe
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    webbrowser.cpp \
    home_dialog.cpp

HEADERS  += mainwindow.h \
    webbrowser.h \
    home_dialog.hpp

RESOURCES += \
    resources.qrc



CONFIG += c++11
