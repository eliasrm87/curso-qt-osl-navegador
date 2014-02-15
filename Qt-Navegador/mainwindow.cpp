#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    browser_ = new WebBrowser;
    setCentralWidget(browser_);

    //Por mi
    toolbarMenu_ = new QToolBar(this);
    this->addToolBar(toolbarMenu_);

   /*for(int i=0; i<browser_->get_tamMarcadores();i++){
        marcadores_.append(new QAction(tr("M"),this));
        toolbarMenu_->addAction(marcadores_.at(i));
        connect(marcadores_.at(i),SIGNAL(triggered()),browser_,SLOT(onLoad2(browser_->get_marcador(i))));
    }*/

   connect(browser_, SIGNAL(sMarcador()), this, SLOT(updateMarcador()));


   mainMenu_ = new QMenuBar(this);
   this->setMenuBar(mainMenu_);

   mnuArchivo_ = new QMenu(tr("&Archivo"), this);
   mainMenu_->addMenu(mnuArchivo_);//añadimos archivo a la barra de menu de arriba

   actArchivoCambiarHome_ = new QAction(tr("&Cambiar pagina de inicio"), this);
   mnuArchivo_->addAction(actArchivoCambiarHome_);
   connect(actArchivoCambiarHome_, SIGNAL(triggered()),this,SLOT(alCambiarHome()));
}

MainWindow::~MainWindow()
{

}

void MainWindow::updateMarcador()
{
    for(int i=0; i<browser_->get_tamMarcadores();i++){
         marcadores_.append(new QAction(browser_->get_nameMarcador(i),this));
         toolbarMenu_->addAction(marcadores_.at(i));
         connect(marcadores_.at(i), SIGNAL(triggered()), browser_, SLOT(onLoad2()));
         marcadores_.at(i)->setData(browser_->get_marcador(i));
    }
}

void MainWindow::alCambiarHome()
{
    QString newHome;
    //FALTA IMPLEMENTAR QUE TE PIDA LA URL DE LA NUEVA PAGINA
   // browse_->set_home(newHome);//FALTA IMPLEMENTAR SET-HOME en webbrowser
}
