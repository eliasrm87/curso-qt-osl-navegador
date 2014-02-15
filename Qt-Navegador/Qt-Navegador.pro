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
    qbookmarkreader.cpp \
    bookmarkvector.cpp

HEADERS  += mainwindow.h \
    webbrowser.h \
    qbookmarkreader.h \
    bookmarkvector.h

RESOURCES += \
    resources.qrc

OTHER_FILES += \
    ../../tmp/bookmark.json

