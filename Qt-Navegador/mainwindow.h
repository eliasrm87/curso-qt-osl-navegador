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
    QMenu* marcadores_;
    QAction * home_;
    QMenu* preferencias_;
    ChangeH * change_;
    QMenu * historial_;

private slots:
    void marcador_s(QString marcador);
    void homePage_s(); //Para crear la ventana y demás necesario para poder pasarle los datos
    void historial_s(QString historial);


};

#endif // MAINWINDOW_H
