#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>

#include "webbrowser.h"
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    //Navegador que se insertará en la ventana.
    WebBrowser *browser_;

    //Barra de menú.
    QMenuBar *mainMenu_;
    //Opción Marcadores para la barra de menú.
    QMenu *mnuMarcadores_;

public slots:
    void onCapturarSignalAnadirMarcador(QString URL);
    void onMarcador();


};

#endif // MAINWINDOW_H
