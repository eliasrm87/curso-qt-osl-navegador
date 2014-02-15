#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    browser_ = new WebBrowser;
    mnu_=  new QMenu("Marcadores");
    preferencias_=new QMenu("Preferencias");
    home_=new QAction("cambiar home",this);
    change_ = new ChangeH;

    preferencias_->addAction(home_);
    setCentralWidget(browser_);
    menuBar()->addMenu(mnu_);
    menuBar()->addMenu(preferencias_);

    connect(browser_,SIGNAL(s_marcador(QString)),this,SLOT(marcador(QString)));
    connect(home_,SIGNAL(triggered()),this,SLOT(homePage()));
    //connect(change_,SIGNAL(s_change(QString),this,SLOT(set_home_page(QString)));
    connect(change_,SIGNAL(s_change(QString)),this,SLOT(set_home_page(QString)));


}
MainWindow::~MainWindow()
{
 delete change_;
}

void MainWindow::marcador(QString marcador)
{
    mnu_->addAction(new QAction(marcador,this));
}
void MainWindow::homePage()
{
  change_->show();

}
void MainWindow::set_home_page(QString home)
{
  //browser_->set_home_page(home);
  browser_->set_home_page(change_->home);
}




