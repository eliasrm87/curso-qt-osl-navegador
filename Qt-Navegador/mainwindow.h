#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>

#include "webbrowser.h"
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void Marcadores();
    void AbrirArchivoMarcadores();
    void MostrarHistorial();

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

    // Menu -> Herramientas
    QMenu      *mnuHerramientas_;
    QAction    *actCambiarHome_;

    // Menu -> Historial
    QMenu      *mnuHistorial_;
    QAction    *actEditarHistorial_;
    QAction    *actBorrarHistorial_;
    QAction    *actMostrarHistorial_;
    QAction    *actHistorial_;

public slots:

    void NuevoMarcador();
    void PulsarMarcador();
    void CambiarHome();
    void BorrarTodoHistorial();


};

#endif // MAINWINDOW_H
