#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "webbrowser.h"
#include <QMenuBar>
#include <QMenu>
#include <QList>
#include <jactionfavorito.h>
#include <QFile>
#include <jdialogo.h>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
  void onFavAnadido(QString url);
  void creaDialogo();

private:
    JDialogo *dialogo_;
    WebBrowser *browser_;
    QMenu *mnuOpciones_;
    QAction *pagInicio_;
    QMenu *mnuFavoritos_;
    QMenuBar *mainMenu_;
    QList<QString> *listaFav_;
};

#endif // MAINWINDOW_H
