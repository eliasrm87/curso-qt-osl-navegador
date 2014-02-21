#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    browser_ = new WebBrowser;
    setCentralWidget(browser_);

    this->setWindowTitle(tr("NAVEGADOR"));
    mainMenu_= new QMenuBar(this);
    mnuArchivo_= new QMenu(tr("&Archivo"),this);
    mainMenu_->addMenu(mnuArchivo_);
    setMenuBar(mainMenu_);

    actArchivoSalir_ = new QAction(QIcon(":/icons/resources/Button-Close-icon.png"),tr("&Salir"),this);
    actArchivoSalir_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_S));
    mnuArchivo_->addAction(actArchivoSalir_);
    connect(actArchivoSalir_, SIGNAL(triggered()),this,SLOT(Salir()));

    mnuAyuda_ = new QMenu(tr("A&yuda"),this);
    mainMenu_->addMenu(mnuAyuda_);
    actAyudaAcerca_ = new QAction(tr("Acerca de"),this);
    mnuAyuda_->addAction(actAyudaAcerca_);
    connect(actAyudaAcerca_, SIGNAL(triggered()),this,SLOT(alAcercaDe()));
}

void MainWindow::Salir()
{
    QMessageBox msg(this);
    msg.setText("<center>¿Salir?</center>");
    msg.addButton("Si",QMessageBox::YesRole);
    msg.addButton("No",QMessageBox::NoRole);
    if (!msg.exec())
        close();
}

void MainWindow::alAcercaDe()
{
    QMessageBox msg(this);
    msg.setWindowTitle(tr("Acerca de"));
    msg.setText("<p>WebBrowser's Aaron (in Qt!)</p><p>v 1.0</p>");
    msg.addButton("Aceptar",QMessageBox::AcceptRole);

    if (msg.exec())
        close();
}


MainWindow::~MainWindow()
{
    mainMenu_->deleteLater();
    mnuArchivo_->deleteLater();
    actArchivoSalir_->deleteLater();
    mnuAyuda_->deleteLater();
    actAyudaAcerca_->deleteLater();
}

