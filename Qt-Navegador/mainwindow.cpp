#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    browser_ = new WebBrowser;

    //Inicializamos los menús
    mainMenu_ = new QMenuBar(this);

    // Archivo
    mnuArchivo_ = new QMenu(tr("&Archivo"), this);
    mainMenu_->addMenu(mnuArchivo_);

    actSalir_ = new QAction(tr("&Salir"), this);
    actSalir_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_X));
    mnuArchivo_->addAction(actSalir_);

    Marcadores();

    connect(actSalir_,  SIGNAL(triggered()), this, SLOT(close()));


    this->setMenuBar(mainMenu_);

    setCentralWidget(browser_);

}

MainWindow::~MainWindow(){}

void MainWindow::Marcadores(){

    mnuMarcadores_ = new QMenu(tr("&Marcadores"), this);
    mainMenu_->addMenu(mnuMarcadores_);

    actNuevoMarcador_ = new QAction(tr("&Añadir a marcadores"), this);
    actNuevoMarcador_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_M));
    mnuMarcadores_->addAction(actNuevoMarcador_);

    AbrirArchivoMarcadores();

    connect(actNuevoMarcador_,  SIGNAL(triggered()), this, SLOT(NuevoMarcador()));


}

void MainWindow::AbrirArchivoMarcadores(){

    QFile file("marcadores.txt");
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "error", file.errorString());
    }

    QTextStream in(&file);

    while(!in.atEnd()) {
        QString line = in.readLine();
        actMarcador_ = new QAction(line, this);
        mnuMarcadores_->addAction(actMarcador_);
        connect(actMarcador_,  SIGNAL(triggered()), this, SLOT(PulsarMarcador()));
    }

    file.close();
}

void MainWindow::NuevoMarcador(){

   QFile file("marcadores.txt");
   file.open(QIODevice::Append);

   QTextStream out(&file);
   QString line = browser_->getAddress();

   out << line << endl;
   actMarcador_ = new QAction(line, this);
   mnuMarcadores_->addAction(actMarcador_);


   /* Close the file */
   file.close();

   //QMessageBox::information(this, "Añadido nuevo", "Se ha añadido el siguiente enlace a marcadores: "+line);

}

void MainWindow::PulsarMarcador(){

    QAction* act = (QAction*) QObject::sender();
    browser_->setAddress(act->text());
}
