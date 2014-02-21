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

#include <QVBoxLayout>
#include <QTabWidget>
#include <QTabBar>
#include <QPushButton>

class MainWindow : public QMainWindow
{
    Q_OBJECT

private slots:
    void Salir();
    void alAcercaDe();

    void new_win();
    void cerrar2();

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();


private:
    WebBrowser *browser_;

    QMenuBar* mainMenu_;
    QMenu* mnuArchivo_;
    QAction* actArchivoAbrir_;
    QAction* actArchivoSalir_;
    QMenu* mnuAyuda_;
    QAction* actAyudaAcerca_;

    QWebView *base_;
    QVBoxLayout *caja_;
    QTabWidget *ventana_;
    QTabBar *tab_;
    QPushButton *salir_;
    QGridLayout *layout_;
    QToolButton *venta_;
};

#endif // MAINWINDOW_H
