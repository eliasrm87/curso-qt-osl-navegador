#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "webbrowser.h"

#include <QMetaObject>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QClipboard>
#include <QKeySequence>
#include <QMessageBox>

class MainWindow : public QMainWindow
{
    Q_OBJECT

private slots:
    void Salir();
    void alAcercaDe();

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    WebBrowser *browser_;

    QMenuBar* mainMenu_;
    QMenu* mnuArchivo_;
    QAction* actArchivoSalir_;
    QMenu* mnuAyuda_;
    QAction* actAyudaAcerca_;
};

#endif // MAINWINDOW_H
