#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QTextStream>
#include "webbrowser.h"
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:

    WebBrowser *browser_;

    QMenuBar* mainMenu_;
    QMenu* mnuMarcadores_;
    QAction* actMarcadorAbrir_;

public slots:
    void capturadorMarcador(QString);
    void marcadorPulsado();
};

#endif // MAINWINDOW_H
