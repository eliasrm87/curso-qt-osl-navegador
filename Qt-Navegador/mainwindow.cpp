#include "mainwindow.h"
#include <QFile>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //Inicializamos
    browser_ = new WebBrowser;
    mn_bar = new QMenuBar(this);
    tabs = new QTabWidget(this);

    actNewTab_ = new QAction(tr("&Nueva Pestaña"),this);
    actNewTab_->setIcon(QIcon(QPixmap(":/icons/resources/new_tab.png")));

    actDeleteTab_ = new QAction(tr("&Cerrar Pestaña"),this);
    actDeleteTab_->setIcon(QIcon(QPixmap(":/icons/resources/remove_tab.png")));

    mn_menu = new QMenu(tr("&Menu "),this);
    mn_config = new QMenu(tr("&Configuración"),this);
    mn_config->setIcon(QIcon(QPixmap(":/icons/resources/tools.png")));
    actChangeHome_ = new QAction(tr("&Parámetros"),this);
    actChangeHome_->setIcon(QIcon(QPixmap(":/icons/resources/params.png")));
    mn_config->addAction(actChangeHome_);
    mn_menu->addMenu(mn_config);

    mnuRecientes_ = new QMenu(tr("&Historial"),this);
    mnuMarcadores_ = new QMenu(tr("&Marcadores"),this);
    actRemoveHistorial_ = new QAction(tr("&Eliminar Historial"),this);
    actRemoveHistorial_->setIcon(QIcon(QPixmap(":/icons/resources/erase.png")));
    mnuShowBkMark_ = new QMenu(tr("&Marcadores"),this);
    mnuShowBkMark_->setIcon(QIcon(QPixmap(":/icons/resources/bookmarks.png")));
    actRemoveBkMark_ = new QAction(tr("&Eliminar Marcadores"),this);
    actRemoveBkMark_->setIcon(QIcon(QPixmap(":/icons/resources/erase.png")));



    //Añadimos los menus
    mn_menu->addAction(actRemoveHistorial_);
    mnuMarcadores_->addMenu(mnuShowBkMark_);
    mnuMarcadores_->addAction(actRemoveBkMark_);
    mn_bar->addMenu(mn_menu);
    mn_bar->addMenu(mnuMarcadores_);
    mn_bar->addMenu(mnuRecientes_);
    mn_bar->addAction(actNewTab_);
    mn_bar->addAction(actDeleteTab_);


    this->setMenuBar(mn_bar);
    this->setCentralWidget(tabs);
    //EMPEZAMOS CON UNA SOLA PESTAÑA
    browser_ = new WebBrowser;
    PointerList_.insert(tabs->currentIndex(), browser_);
    tabs->addTab(browser_, "Nueva Pestaña");

    connections();

}

MainWindow::~MainWindow()
{
    //Eliminamos el historial y salimos
    if(browser_->delete_historial)
        onRemove(false);

   browser_->deleteLater();
   mn_menu->deleteLater();
   mn_config->deleteLater();
   actChangeHome_->deleteLater();
   mn_bar->deleteLater();
   mnuRecientes_->deleteLater();
   actRemoveHistorial_->deleteLater();

   mnuMarcadores_->deleteLater();
   mnuShowBkMark_->deleteLater();
   actRemoveBkMark_->deleteLater();
   tabs->clear();
   tabs->deleteLater();

}

void MainWindow::connections()
{

    connect(browser_,           SIGNAL(marcadores(bool,QString)), this,          SLOT(onAdd(bool,QString)));
    connect(browser_,           SIGNAL(historial(bool,QString)),  this,          SLOT(onAdd(bool,QString)));
    connect(actRemoveHistorial_,&QAction::triggered,                             [&](){   onRemove(false); });
    connect(actRemoveBkMark_,   &QAction::triggered,                             [&](){   onRemove(true); });
    connect(actChangeHome_,     &QAction::triggered,                             [&](){   browser_->dialogo.showNormal();    });
    connect(actNewTab_,         SIGNAL(triggered()),             this,           SLOT(newTab()));
    connect(actDeleteTab_,      SIGNAL(triggered()),              this,          SLOT(deleteTab()));
    connect(browser_,           SIGNAL(name(QString)),              this,        SLOT(onLoadTab(QString)));
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
            actAbrir->setIcon(QIcon(QPixmap(":/icons/resources/bookmarks.png")));
            mnuShowBkMark_->addAction(actAbrir);

            connect(actAbrir, SIGNAL(triggered()), this, SLOT(onLoadTab()));
             marcadores.close();
        }


        }



        if (recientes.open(QIODevice::ReadOnly | QIODevice::Text)) {

            // Obtenemos las reproducciones recientes
            QTextStream in(&recientes);
            while (!in.atEnd()) {
                QString archivo = in.readLine();
                QAction *actAbrir = new QAction(archivo, this);
                actAbrir->setIcon(QIcon(QPixmap(":/icons/resources/main_icon.png")));
                mnuRecientes_->addAction(actAbrir);
                connect(actAbrir, SIGNAL(triggered()), this, SLOT(onLoadTab()));

                recientes.close();


                }
        }
}



void MainWindow :: onAdd(bool option,QString url){


if (option){
     QFile  marcadores("./marcadores.txt");
   if(marcadores.open(QIODevice::Append)){
        QTextStream out(&marcadores);
        out << url << endl;
        QAction *actAbrir= new QAction(url, this);
        actAbrir->setIcon(QIcon(QPixmap(":/icons/resources/bookmarks.png")));
        mnuShowBkMark_->addAction(actAbrir);
        connect(actAbrir, SIGNAL(triggered()), this, SLOT(onLoadTab()));
        marcadores.close();
    }
}

else{
    QFile  recientes("./historial.txt");
    if(recientes.open(QIODevice::Append)){
        QTextStream out(&recientes);
        out << url << endl;
        QAction *actAbrir = new QAction(url, this);
        actAbrir->setIcon(QIcon(QPixmap(":/icons/resources/main_icon.png")));
        mnuRecientes_->addAction(actAbrir);
        connect(actAbrir, SIGNAL(triggered()), this, SLOT(onLoadTab()));
        recientes.close();
    }
}


}

void MainWindow::newTab(){

    if (tabs->count() < 10){ //Solo dejamos 10 pestañas
        WebBrowser *buscador = new WebBrowser;
        tabs->addTab(buscador, "Nueva Pestaña");
        tabs->setTabIcon(tabs->currentIndex(),QIcon(QPixmap(":/icons/resources/main_icon.png")));
    }
}
void MainWindow::deleteTab()
{
      if(tabs->count() > 0){
         int aux = tabs->currentIndex();
          tabs->setCurrentIndex(0);
        PointerList_.at(aux)->deleteLater();
        tabs->removeTab(aux);
      }

  if(tabs->count() == 0)
      this->close();
}


void MainWindow::onLoadTab()
{


   QAction *accion = (QAction*)QObject::sender();
   PointerList_.at(tabs->currentIndex())->onUrlChange(accion->text());
    PointerList_.at(tabs->currentIndex())->onLoad();
    tabs->setTabText(tabs->currentIndex(),accion->text());


}


