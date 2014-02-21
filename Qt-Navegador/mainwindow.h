//La clase msgInput no me funciona, por lo que no pude sacar una ventana para añdir el nombre
// del marcador, ni seleccionar una pagina de favoritos, sino que coga en la que estas

//Como nose sacar otra ventana, tampoco se mostrar el historial y dar la opcion de modificarlo


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "webbrowser.h"
#include "msginput.h"
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
    QMenu* mnuVer_;
    QAction* actVerHistorial_;

private slots:
    void updateMarcador();
    void alCambiarHome();
    void alHistorial();
};

#endif // MAINWINDOW_H
