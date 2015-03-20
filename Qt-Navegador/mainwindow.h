#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "webbrowser.h"
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QFile>
#include <QString>
#include <QFile>
#include <QTextStream>
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    WebBrowser *browser_;
    QMenuBar *mainmenu_;
    QAction *actmarc_;
    QMenu *marcadores_;
    QMenu *inicio_;
    QAction* cambiarinicio_;

public slots:
    void guardarmarcador(QString);
    void onmarcador();
    void change(QString url);
};

#endif // MAINWINDOW_H
