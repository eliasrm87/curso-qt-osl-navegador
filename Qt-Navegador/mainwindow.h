#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "webbrowser.h"
//por mi-------
#include <QToolBar>
#include <QAction>
#include <QVariant>
#include <QMenuBar>
#include <QMenu>
//------
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    WebBrowser *browser_;
    //Por mi
    QToolBar *toolbarMenu_;
    QVector<QAction*> marcadores_;
    QMenuBar* mainMenu_;
    QMenu* mnuArchivo_;
    QAction* actArchivoCambiarHome_;

private slots:
    void updateMarcador();
    void alCambiarHome();
};

#endif // MAINWINDOW_H
