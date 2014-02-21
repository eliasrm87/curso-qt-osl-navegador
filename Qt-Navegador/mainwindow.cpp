#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    browser_ = new WebBrowser;
    setCentralWidget(browser_);

    //this->setWindowTitle();

    main_menu_= new QMenuBar(this);
    menu_archivo_= new QMenu ("Archivo", this);
    main_menu_->addMenu(menu_archivo_);
    setMenuBar(main_menu_);

    Salir_ = new QAction("salir", this);
    menu_archivo_->addAction(Salir_);

    connect(Salir_,SIGNAL(triggered()), this, SLOT(Salir()));


    //menuBar();
}

MainWindow::~MainWindow()
{

}


void MainWindow::Salir(){

    QMessageBox msg;
    msg.move(200,200);

    msg.setText("DESEA SALIR REALMENTE?");
    msg.addButton("SI", QMessageBox::YesRole);
    msg.addButton("NO", QMessageBox::NoRole);

    if (!msg.exec())
        close();

}

