#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    browser_ = new WebBrowser;
    // Cargamos la configuración guardada
    browser_->loadSettings();
    browser_->GoHome();

    //Inicializamos los menús
    mainMenu_ = new QMenuBar(this);

    // Archivo
    mnuArchivo_ = new QMenu(tr("&Archivo"), this);
    mainMenu_->addMenu(mnuArchivo_);

    // Archivo > Salir
    actSalir_ = new QAction(tr("&Salir"), this);
    actSalir_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_X));
    mnuArchivo_->addAction(actSalir_);

    // Marcadores
    Marcadores();

    // Herramientas
    mnuHerramientas_ = new QMenu(tr("&Herramientas"), this);
    mainMenu_->addMenu(mnuHerramientas_);

    actCambiarHome_ = new QAction(tr("&Convertir en pagina de inicio ..."), this);
    actCambiarHome_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_P));
    mnuHerramientas_->addAction(actCambiarHome_);

    // Historial
    mnuHistorial_ = new QMenu(tr("&Historial"), this);
    mainMenu_->addMenu(mnuHistorial_);


    actEditarHistorial_ = new QAction(tr("&Editar historial"), this);
    actEditarHistorial_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_H));
    mnuHistorial_->addAction(actEditarHistorial_);


    actBorrarHistorial_ = new QAction(tr("&Borrar todo el historial"), this);
    actBorrarHistorial_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_D));
    mnuHistorial_->addAction(actBorrarHistorial_);

    MostrarHistorial();

    // Conexiones
    connect(actSalir_,  SIGNAL(triggered()), this, SLOT(close()));
    connect(actCambiarHome_,  SIGNAL(triggered()), this, SLOT(CambiarHome()));
    connect(actBorrarHistorial_,  SIGNAL(triggered()), this, SLOT(BorrarTodoHistorial()));


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
   connect(actMarcador_,  SIGNAL(triggered()), this, SLOT(PulsarMarcador()));


   /* Close the file */
   file.close();

   //QMessageBox::information(this, "Añadido nuevo", "Se ha añadido el siguiente enlace a marcadores: "+line);

}

void MainWindow::PulsarMarcador(){

    QAction* act = (QAction*) QObject::sender();
    browser_->setAddress(act->text());
}

// CambiarHome: cambia la página de inicio por la que este actualmente en la barra de direcciones
void MainWindow::CambiarHome(){

    QString url = browser_->getAddress();
    browser_->setHomeAddress(url);
    //ebrowser_->saveSettings(url);
}

void MainWindow::MostrarHistorial(){

    QFile file("historial.txt");
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "error", file.errorString());
    }

    QTextStream in(&file);

    while(!in.atEnd()) {
        QString line = in.readLine();
        actHistorial_ = new QAction(line, this);
        mnuHistorial_->addAction(actHistorial_);
        connect(actHistorial_,  SIGNAL(triggered()), this, SLOT(PulsarMarcador()));
    }

    file.close();

}

void MainWindow::BorrarTodoHistorial(){

    QFile file("historial.txt");
    file.open(QIODevice::Truncate | QIODevice::Text | QIODevice::ReadWrite);

    file.close();
}
