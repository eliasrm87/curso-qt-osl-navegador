#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    browser_ = new WebBrowser;
    mainMenu_= new QMenuBar(this);

    //Marcadores
    mnuMarcadores_ = new QMenu (tr("&Marcadores"), this);//Especificamos el texto del menu
    mainMenu_-> addMenu(mnuMarcadores_);
    //Historial
    mnuHistorial_ = new QMenu (tr("&Historial"), this);//Especificamos el texto del menu
    mainMenu_-> addMenu(mnuHistorial_);



    //acciones
    //añadir
    actAddMarcadores_ = new QAction(tr("&AñadirMarcadores"),this);
    mnuMarcadores_->addAction(actAddMarcadores_);
    VerMarcadores();


    //Conexiones
    //Conectamos las aciones de los menus con nuestros slots
    connect(actAddMarcadores_, SIGNAL(triggered()),this, SLOT (AddMarcadores()));


    //Añadimos la barra menu
    this->setMenuBar(mainMenu_);
    this->setCentralWidget(browser_);

}

MainWindow::~MainWindow()
{

}
void MainWindow::VerMarcadores(){
    QFile file("marcadores.txt");
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);

    while(!in.atEnd()) {
        QString line = in.readLine();
        actVerMarcadores_= new QAction(line,this);
        mnuMarcadores_->addAction(actVerMarcadores_);
        connect(actVerMarcadores_,SIGNAL(triggered()),this,SLOT(PulsarMarcador()));
    }

    file.close();
}
void MainWindow::AddMarcadores(){
    QFile file("marcadores.txt");
    file.open(QIODevice::Append);

    QTextStream out(&file);

    QString linea = browser_->getAddress();

    out << linea << endl;//Escribimos
    actVerMarcadores_= new QAction(linea,this);
    mnuMarcadores_->addAction(actVerMarcadores_);

    file.close();
}

void MainWindow::PulsarMarcador()
{
    QAction* act = (QAction*)QObject::sender();//Puntero al objeto que envio la señal que activo este slot
    browser_->setAddress(act->text());
}
