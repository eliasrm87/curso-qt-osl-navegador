#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "webbrowser.h"
#include <QMenu>
#include <QMenuBar>
#include <QGridLayout>
#include <QAction>
#include <QTabWidget>
#include <QList>
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:

    WebBrowser      *browser_;
    QMenu*          mn_menu;
    QMenu*          mn_config;
    QAction*        actChangeHome_;

    QMenuBar*       mn_bar;
    QMenu*          mnuRecientes_;
    QAction*        actRemoveHistorial_;

    QMenu*          mnuMarcadores_;
    QMenu*          mnuShowBkMark_;
    QAction*        actRemoveBkMark_;



    QTabWidget          *tabs;
    QAction*            actNewTab_;
    QAction*            actDeleteTab_;
    QList<WebBrowser*>  PointerList_;
    void connections();

public slots:

    //Historial
    void onSee();
    void onRemove(bool);
    void onAdd(bool,QString);

    void newTab();
    void deleteTab();
    void onLoadTab();
};

#endif // MAINWINDOW_H
