#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "webbrowser.h"
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QFile>
#include <QString>
#include <QList>
#include <QDialog>
#include <QRect>
#include "editarhistorial.h"
#include <QResizeEvent>
#include <QDialogButtonBox>

#include <QDesktopWidget>
#include <QPushButton>
#include <QToolButton>


#include <iostream>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void resizeEvent(QResizeEvent* event);

private slots:
    void setNuevoMarcador();
    void showMarcadores();
    void showHistorial();
    void editHistorial();
    void setActualMarcador();
    void setHomePageW();
    void crearMenu();
    void borrarHistorial();
    void crearPestana();
    void cerrarPestana(const int &index);
    void menuPestanas();
    void mostrarBotonMas();
    void activateTab(int index);
    void llamarCerrarPestana();
    void cerarVentana();
    void restaurarSesion();
    void menuSesion();


private:
    //WebBrowser *browser_;
    QMenuBar *mainMenu_;
    QMenu *mnuArchivo_;
    QMenu *mnuMarcadores_;
    QMenu *mnuHistorial_;
    QMenu *mnuPestanas_;
    QMenu *mnuSesion_;
    QMenu *mnuMostrarMarcadores_;
    QMenu *mnuMostrarHistorial_;
    QAction *actArchivoSalir_;
    QAction *actMarcadoresNuevo_;
    QAction *actMarcadoresHome_;
    QAction *actHistorialEditar_;
    QAction *actHistorialBorrar_;
    QAction *actPestanasNueva_;
    QAction *actPestanasCerrar_;
    QAction *actSesionRestaurar_;
    QTabWidget *tabs_;
    QPushButton* mas_;
    QList<WebBrowser*> browserList_;

    int pestanaActual_;

};

#endif // MAINWINDOW_H
