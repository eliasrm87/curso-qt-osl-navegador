#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "webbrowser.h"
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QMessageBox>
#include <QFile>
#include <QLineEdit>
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void VerMarcadores();

private:
    WebBrowser *browser_;
    //Añadimos un menu
     QMenuBar* mainMenu_;
     QMenu* mnuMarcadores_;
     QMenu* mnuHistorial_;
     QMenu* mnuHerramientas_;

     //Acciones
     QAction* actAddMarcadores_;
     QAction* actVerMarcadores_;
     QAction* actCambiarInicio_;

     QString txtAdress;

public slots:

     void AddMarcadores();
     void PulsarMarcador();
     void CambiarInicio();
};

#endif // MAINWINDOW_H
