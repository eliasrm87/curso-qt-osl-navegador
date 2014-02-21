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

   mnuVer_ = new QMenu(tr("&Ver"),this);
   mainMenu_->addMenu(mnuVer_);


   actVerHistorial_ = new QAction(tr("&Historial"), this);
   mnuVer_->addAction(actVerHistorial_);
   connect(actVerHistorial_, SIGNAL(triggered()),this,SLOT(alHistorial()));
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

//Esta funcion no funciona
void MainWindow::alCambiarHome()
{
    msgInput ventana("Escribe pagina de inicio");
    QString newHome = ventana.get_dato();
    if(newHome != "NULL")
        browser_->set_inicialPage(newHome);
}

void MainWindow::alHistorial()
{

    QWidget ventana;
    ventana.setWindowTitle("Historial");
    for(int i=0; i<browser_->tam_historial();i++){
        ventana.setWhatsThis(browser_->get_historial(i));
    }
    ventana.show();
}
