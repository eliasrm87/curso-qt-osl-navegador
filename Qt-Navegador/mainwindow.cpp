#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    browser_ = new WebBrowser;
    setCentralWidget(browser_);

    // Inicializamos los elementos del menú
    mainMenu_ = new QMenuBar(this);
    mnuNavegador_ = new QMenu(tr("Navegador"), this);
    mnuMarcadores_ = new QMenu(tr("Marcadores"), this);
    mnuMarcadoresVer_ = new QMenu(tr("Ver marcadores"), this);

    // Inicializamos las acciones
    actNavegadorSalir_ = new QAction(tr("Salir"), this);
    actMarcadoresAgregar_ = new QAction(tr("Agregar marcador"), this);

    // Agregamos los menús y las acciones
    mainMenu_->addMenu(mnuNavegador_);
    mnuNavegador_->addAction(actNavegadorSalir_);
    mainMenu_->addMenu(mnuMarcadores_);
    mnuMarcadores_->addAction(actMarcadoresAgregar_);
    mnuMarcadores_->addSeparator();
    mnuMarcadores_->addMenu(mnuMarcadoresVer_);

    // Conectamos las acciones a los slots
    connect(actNavegadorSalir_, SIGNAL(triggered()), this, SLOT(alSalir()));
    connect(actMarcadoresAgregar_, SIGNAL(triggered()), this, SLOT(alMarcador()));

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

void MainWindow::alMarcador()
{
    // Obtenemos el marcador
    QString marcador = browser_->getAddress();

    // Lo añadimos dinámicamente como acción
    QAction *actGoMarcador;
    actGoMarcador = new QAction(marcador, this);
    mnuMarcadoresVer_->addAction(actGoMarcador);
    connect(actGoMarcador, SIGNAL(triggered()), this, SLOT(irMarcador()));
}

void MainWindow::irMarcador()
{
    QAction *accion = (QAction*)QObject::sender();
    browser_->setAddress(accion->text());
}
