#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QFile>
#include <QMessageBox>
#include "webbrowser.h"
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void Marcadores();
    void AbrirArchivoMarcadores();

private:

    WebBrowser *browser_;

    // Barra de Menu
    QMenuBar   *mainMenu_;

    // Menu -> Archivo
    QMenu      *mnuArchivo_;
    QAction    *actSalir_;

    // Menu -> Marcadores
    QMenu      *mnuMarcadores_;
    QAction    *actNuevoMarcador_;
    QAction    *actMarcador_;

public slots:

    void NuevoMarcador();
    void PulsarMarcador();


};

#endif // MAINWINDOW_H
