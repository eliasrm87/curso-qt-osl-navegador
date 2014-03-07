#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "webbrowser.h"
#include "changehp.h"
#include <QMenuBar>
#include <QMenu>
#include <QAction>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    WebBrowser *browser_;
    QMenu* mnuMarcador_;
    QMenu* mnuPreferencias_;
    QAction* actMarGuardar;
    QAction* actPreferencias;
    ChangeHP* changehp_;

public slots:
    void alMarcador();
    void changeHomePage();
};

#endif // MAINWINDOW_H
