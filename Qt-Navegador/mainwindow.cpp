#include "mainwindow.h"
#include <QFile>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //Inicializamos
    browser_ = new WebBrowser;
    mn_bar = new QMenuBar(this);

    mn_menu = new QMenu(tr("&Menu "),this);
    mn_config = new QMenu(tr("&Configuración"),this);
    actChangeHome_ = new QAction(tr("&Establecer Home"),this);
    mn_config->addAction(actChangeHome_);
    mn_menu->addMenu(mn_config);

    mnuRecientes_ = new QMenu(tr("&Historial"),this);
    mnuMarcadores_ = new QMenu(tr("&Marcadores"),this);
    actRemoveHistorial_ = new QAction(tr("&Eliminar Historial"),this);
    mnuShowBkMark_ = new QMenu(tr("&Marcadores"),this);
    actShowBkMark_ = new QAction(tr("&Recargar Marcadores Marcadores"),this);
    actRemoveBkMark_ = new QAction(tr("&Eliminar Marcadores"),this);
    actCargarMarcador_ = new QAction(this);

    //Añadimos los menus
    mn_menu->addAction(actRemoveHistorial_);
    mnuMarcadores_->addMenu(mnuShowBkMark_);
    mnuMarcadores_->addAction(actShowBkMark_);
    mnuMarcadores_->addAction(actRemoveBkMark_);
    mn_bar->addMenu(mn_menu);
    mn_bar->addMenu(mnuMarcadores_);
    mn_bar->addMenu(mnuRecientes_);



    this->setCentralWidget(browser_);
    this->setMenuBar(mn_bar);


    connections();

}

MainWindow::~MainWindow()
{

}

void MainWindow::connections()
{

    connect(browser_,           SIGNAL(marcadores(bool,QString)), this,          SLOT(onAdd(bool,QString)));
    connect(browser_,           SIGNAL(historial(bool,QString)),  this,          SLOT(onAdd(bool,QString)));
    connect(actShowBkMark_,     &QAction::triggered,                             [&](){   onSee(); });
    connect(actRemoveHistorial_,&QAction::triggered,                             [&](){   onRemove(false); });
    connect(actRemoveBkMark_,   &QAction::triggered,                             [&](){   onRemove(true); });
    connect(actChangeHome_,     &QAction::triggered,                             [&](){   browser_->dialogo.showNormal();    });
    //Cargamos los marcadores y el historial
    onSee();

}

void MainWindow :: onRemove(bool i){

    QFile  marcadores("./marcadores.txt");
    QFile  recientes("./historial.txt");

    if(i){

    if (marcadores.open(QIODevice::ReadWrite | QIODevice::Text)) {

            marcadores.resize(0);
            marcadores.close();
            mnuShowBkMark_->clear();
        }

        marcadores.close();
    }

    if (!i){

        if (recientes.open(QIODevice::Append | QIODevice::Text)) {
            recientes.resize(0);
            recientes.close();
            mnuRecientes_->clear();
        }

        recientes.close();
    }

}

void MainWindow :: onSee(){

    QFile  marcadores("./marcadores.txt");
    QFile  recientes("./historial.txt");
     if (marcadores.open(QIODevice::ReadOnly | QIODevice::Text)) {

         QTextStream in(&marcadores);

        while (!in.atEnd()) {
            QString archivo = in.readLine();
            QAction *actAbrir= new QAction(archivo, this);
            mnuShowBkMark_->addAction(actAbrir);

            connect(actAbrir, SIGNAL(triggered()), this, SLOT(onLoad()));
             marcadores.close();
        }


        }



        if (recientes.open(QIODevice::ReadOnly | QIODevice::Text)) {

            // Obtenemos las reproducciones recientes
            QTextStream in(&recientes);
            while (!in.atEnd()) {
                QString archivo = in.readLine();
                QAction *actAbrir = new QAction(archivo, this);
                mnuRecientes_->addAction(actAbrir);
                connect(actAbrir, SIGNAL(triggered()), this, SLOT(onLoad()));

                recientes.close();


                }
        }
}


void MainWindow :: onLoad(){

    QAction *accion = (QAction*)QObject::sender();
    browser_->onUrlChange(accion->text());


}

void MainWindow :: onAdd(bool option,QString url){

    QFile  marcadores("./marcadores.txt");
    QFile  recientes("./historial.txt");

if (option){

   if(marcadores.open(QIODevice::Append)){
        QTextStream out(&marcadores);
        out << url << endl;
        QAction *actAbrir= new QAction(url, this);
        mnuShowBkMark_->addAction(actAbrir);
        connect(actAbrir, SIGNAL(triggered()), this, SLOT(onLoad()));
        marcadores.close();
    }
}

else{

    if(recientes.open(QIODevice::Append)){
        QTextStream out(&recientes);
        out << url << endl;
        QAction *actAbrir = new QAction(url, this);
        mnuRecientes_->addAction(actAbrir);
        connect(actAbrir, SIGNAL(triggered()), this, SLOT(onLoad()));
        recientes.close();
    }
}


}


