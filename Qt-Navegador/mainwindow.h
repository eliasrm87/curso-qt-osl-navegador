/*
 *  Adrián Rodríguez Bazaga
 *  alu0100826456@ull.edu.es
 *  Navegador web - Curso de QT
 *
 * */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#pragma once
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QFile>
#include <QString>
#include <QList>
#include <QDialog>
#include <QRect>
#include "webbrowser.h"
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    //Implementacion en clase
    void setupMenu();                       //Para inicializar todo el menú
    void setNuevoMarcador();
    void showMarcadores();
    void refreshMarcadores();
    void showHistorial();
    void refreshHistorial();
    void limpiarHistorial();
    void setActualMarcador();
    void setPagPrincipal();

private:
    WebBrowser *browser_;
    //Implementacion en clase
    QMenuBar *mainMenu_;
    QMenu *mnuArchivo_;
    QMenu *mnuMarcadores_;
    QMenu *mnuMostrarMarcadores_;
    QMenu *mnuHistorial_;
    QMenu *mnuVerHistorial_;
    QMenu *mnuLimpiarHistorial_;

    QAction *actArchivoSalir_;
    QAction *actMarcadoresNuevo_;
    QAction *actMarcadoresHome_;
};

#endif // MAINWINDOW_H
