#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "webbrowser.h"
class MainWindow : public QMainWindow
{
    Q_OBJECT

//hola
private slots:
    void Salir();


public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    WebBrowser *browser_;

    QMenuBar *main_menu_;
    QMenu *menu_archivo_;
    QAction *Salir_;

};

#endif // MAINWINDOW_H
