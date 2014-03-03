#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    browser_ = new WebBrowser;
    setCentralWidget(browser_);

    // Inicializamos los elementos del menú
    mainMenu_ = new QMenuBar(this);
    mnuNavegador_ = new QMenu(tr("Navegador"), this);
    actNavegadorSalir_ = new QAction(tr("Salir"), this);

    // Agregamos los menús y las acciones
    mainMenu_->addMenu(mnuNavegador_);
    mnuNavegador_->addAction(actNavegadorSalir_);

    // Conectamos las acciones a los slots
    connect(actNavegadorSalir_, SIGNAL(triggered()), this, SLOT(alSalir()));

    // Agregamos el menú al layout
    setMenuBar(mainMenu_);

}

MainWindow::~MainWindow()
{

}

void MainWindow::alSalir()
{
    exit(0);
}
