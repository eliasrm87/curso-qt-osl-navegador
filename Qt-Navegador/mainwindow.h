#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QInputDialog>
#include "webbrowser.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void alSalir();
    void alMarcador();
    void irMarcador();
    void alHomepage();
    void borrarHistorial();
    void alHistorial();

private:
    WebBrowser *browser_;

    // Barra de menú
    QMenuBar *mainMenu_;

    // Elementos del menú
    QMenu *mnuNavegador_;
    QMenu *mnuMarcadores_;
    QMenu *mnuMarcadoresVer_;
    QMenu *mnuHerramientas_;
    QMenu *mnuHistorial_;
    QMenu *mnuHistorialVer_;

    // Acciones del menú
    QAction *actNavegadorSalir_;
    QAction *actMarcadoresAgregar_;
    QAction *actHerramientasHomepage_;
    QAction *actHistorialBorrar_;
};

#endif // MAINWINDOW_H
