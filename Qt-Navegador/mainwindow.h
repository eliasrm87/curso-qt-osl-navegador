#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "webbrowser.h"
#include "changeh.h"
#include <QMenuBar>
#include <QAction>
#include <QSettings>
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    WebBrowser *browser_;
    QMenu* mnu_;
    QAction * home_;
    QMenu* preferencias_;
    ChangeH * change_;

private slots:
    void marcador(QString marcador);
    void homePage(); //Para crear la ventana y demás necesario para poder pasarle los datos



};

#endif // MAINWINDOW_H
