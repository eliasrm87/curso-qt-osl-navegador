#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    browser_ = new WebBrowser;
    mnu_=  new QMenu("Marcadores");
    preferencias_=new QMenu("Preferencias");
    home_=new QAction("cambiar home",this);
    preferencias_->addAction(home_);
    setCentralWidget(browser_);
    menuBar()->addMenu(mnu_);
    menuBar()->addMenu(preferencias_);
    connect(browser_,SIGNAL(s_marcador(QString)),this,SLOT(marcador(QString)));
    connect(home_,SIGNAL(triggered()),this,SLOT(setHome()));

}

MainWindow::~MainWindow()
{


}

void MainWindow::marcador(QString marcador)
{

    mnu_->addAction(new QAction(marcador,this));
}
void MainWindow::setHome()
{
  ChangeH * change = new ChangeH();
  change->show();

}




