#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QMessageBox>
#include <QMenu>
#include <QKeyEvent>
#include <QTouchEvent>
#include <QInputDialog>
#include <QSettings>
#include <QApplication>
#include <QProcess>
#include <QFileOpenEvent>
#include "webbrowser.h"
#include "record.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT //directiva al prepocesador de QT, primero lo convierten a c++ y luego lo precomplian en QT.
private:
    Record     *historial_;
    Record     *marcador_;
    WebBrowser *browser_;
    QMenuBar  *mainMenu_;
    QMenu      *mnuNavegador_;

    QMenu      *mnuMarcadores_;
    QMenu      *mnuVerMarcadores_;
    QAction    *actMarcadoresBorrar_;
    QAction    *actMarcadoresAñadir_;

    QMenu      *mnuHerramientas_;
    QAction    *actHerramientasHomepage_;
    QAction    *actHerramientasConfig_;

    QMenu      *mnuHistorial_;
    QAction    *actHistorialMostrar_;
    QAction    *actHistorialBorrar_;


    QMenu      *mnuVer_;
    QAction    *actVerZoomPlus_;
    QAction    *actVerZoomLess_;

    QAction     *actionReboot;

private:
    void setupConnections();
    void barraMenu();
    void readSettings();
    void writeSettings();

private slots:
    bool alSalir();
    void homePage();
    void eraseConfig();
    void slotReboot();
    void cleanRecord();
    void cleanMarcador();
    void toRecord();
    void loadWeb();
    void loadRecord();
    void toMarcador();
    void loadMarcador();

public:
    static int const EXIT_CODE_REBOOT;
    bool eventFilter(QObject *object, QEvent *event);
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
};

#endif // MAINWINDOW_H


/*El QMainWinows viene con su propio layaout predefinido*/
