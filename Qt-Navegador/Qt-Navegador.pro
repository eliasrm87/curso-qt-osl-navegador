#-------------------------------------------------
#
# Project created by QtCreator 2014-02-11T17:47:37
#
#-------------------------------------------------

QT       += core gui webkitwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Qt-Navegador-exe
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    webbrowser.cpp \
    markerswindow.cpp \
    historywindow.cpp \
    urllistdialog.cpp

HEADERS  += mainwindow.h \
    webbrowser.h \
    markerswindow.h \
    historywindow.h \
    urllistdialog.h

RESOURCES += \
    resources.qrc

