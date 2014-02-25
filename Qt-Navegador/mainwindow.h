#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QStringList>
#include <QFile>
#include <QMessageBox>

#include "webbrowser.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    WebBrowser *browser_;

    // Barra de menu
    QMenuBar* mainMenu_;
    QMenu* mnuArchivo_;
    QMenu* mnuEditar_;
    QMenu* mnuVer_;
    QMenu* mnuHistorial_;
    QMenu* mnuMarcadores_;
    QMenu* mnuHerramientas_;
    QMenu* mnuAyuda_;

    // Lista de Marcadores
    QStringList bookmarkList;
    QAction* actAddBookmark_;
    QAction* actSetHomepage_;

    // Historial
    QAction* actDeleteHistory_;

    // Zoom
    QAction* actPlusZoom;
    QAction* actMinusZoom_;
    double zoomVar;

private:
    void readBookmarkFile();

public slots:
    void addMarcador();
    void PulsarMarcador();
    void showHistory();
    void deleteHistory();
    void setPlusZoom();
    void setMinusZoom();
};

#endif // MAINWINDOW_H
