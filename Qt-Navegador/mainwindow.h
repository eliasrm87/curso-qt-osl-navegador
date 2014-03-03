#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include "webbrowser.h"
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void alSalir();

private:
    WebBrowser *browser_;

    // Barra de menú
    QMenuBar *mainMenu_;

    // Elementos del menú
    QMenu *mnuNavegador_;

    // Acciones del menú
    QAction *actNavegadorSalir_;

};

#endif // MAINWINDOW_H
