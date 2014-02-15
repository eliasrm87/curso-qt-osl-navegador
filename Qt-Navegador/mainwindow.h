#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "webbrowser.h"
#include "changeh.h"
#include <QMenuBar>
#include <QAction>
#include <QSettings>
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    WebBrowser *browser_;
    QMenu* mnu_;
    QAction * home_;
    QMenu* preferencias_;

private slots:
    void marcador(QString marcador);
    void setHome();


};

#endif // MAINWINDOW_H
