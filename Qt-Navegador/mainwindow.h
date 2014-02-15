#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "webbrowser.h"
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QFile>
#include <QString>
#include <QList>
#include <QDialog>
#include <QRect>
#include "editarhistorial.h"

#include <iostream>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void setNuevoMarcador();
    void showMarcadores();
    void showHistorial();
    void editHistorial();
    void setActualMarcador();
    void setHomePageW();

private:
    WebBrowser *browser_;
    QMenuBar *mainMenu_;
    QMenu *mnuArchivo_;
    QMenu *mnuMarcadores_;
    QMenu *mnuMostrarMarcadores_;
    QMenu *mnuMostrarHistorial_;
    QAction *actArchivoSalir_;
    QAction *actMarcadoresNuevo_;
    QAction *actMarcadoresHome_;
    QAction *actMarcadoresHistorialEditar_;

    QList<QAction*> actMarcadoresLista_;
};

#endif // MAINWINDOW_H
