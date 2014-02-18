#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    browser_ = new WebBrowser;
    marcadores_=  new QMenu("Marcadores");
    preferencias_=new QMenu("Preferencias");
    home_=new QAction("cambiar home",this);
    historial_=new QMenu ("Historial");
    change_ = new ChangeH;

    preferencias_->addAction(home_);
    setCentralWidget(browser_);
    menuBar()->addMenu(marcadores_);
    menuBar()->addMenu(preferencias_);
    menuBar()->addMenu(historial_);

    connect(browser_,SIGNAL(s_marcador(QString)),this,SLOT(marcador_s(QString)));
    connect(home_,SIGNAL(triggered()),this,SLOT(homePage_s()));
    connect(change_,SIGNAL(s_change(QUrl)),browser_, SLOT(set_home_page_s(QUrl)));
    connect(browser_,SIGNAL(s_historial(QString)),this,SLOT(historial_s(QString)));


}
MainWindow::~MainWindow()
{
 delete change_;
}

void MainWindow::marcador_s(QString marcadores)
{
    marcadores_->addAction(new QAction(marcadores,this));
}
void MainWindow::homePage_s()
{
  change_->show();

}
void MainWindow::historial_s(QString historial)
{
    historial_->addAction(new QAction(historial,this));
}





