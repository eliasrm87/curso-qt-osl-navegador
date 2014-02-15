#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    browser_ = new WebBrowser;
    setCentralWidget(browser_);

    //MARCADORES
    mnuMarcador_ = new QMenu("Marcador");
    menuBar()->addMenu(mnuMarcador_);

    actMarGuardar = new QAction ("Guardar Marcador", this);
    mnuMarcador_ ->addAction(actMarGuardar);

    connect(actMarGuardar, SIGNAL(triggered()), this, SLOT(alMarcador())); //Guardar Marcador desde Menu
    connect(browser_, SIGNAL(smarcador(QString)), this, SLOT(alMarcador())); //Guardar Marcador desde Boton

    //PREFERENCIAS

    mnuPreferencias_ = new QMenu("Preferencias");
    menuBar()->addMenu(mnuPreferencias_);

    actPreferencias = new QAction ("Cambiar HomePage", this);
    mnuPreferencias_ ->addAction(actPreferencias);

    connect(actPreferencias, SIGNAL(triggered()), this, SLOT(changeHomePage()));

}

MainWindow::~MainWindow()
{

}

void MainWindow::alMarcador()
{
    QAction* act = new QAction(browser_->address(), this);
    mnuMarcador_->addAction(act);
}

void MainWindow::changeHomePage()
{
    ChangeHP* dialog = new ChangeHP;
    dialog->show();
}

