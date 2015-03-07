#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "webbrowser.h"
#include <QMenu>
#include <QMenuBar>
#include <QGridLayout>
#include <QAction>


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
    QAction*        actCargarMarcador_;

    QMenu*          mnuMarcadores_;
    QAction*        actShowBkMark_;
    QMenu*          mnuShowBkMark_;
    QAction*        actRemoveBkMark_;

    QAction*         actZoom_;

    void connections();


public slots:

    //Historial
    void onSee();
    void onLoad();
    void onRemove(bool);
    void onAdd(bool,QString);


};

#endif // MAINWINDOW_H
