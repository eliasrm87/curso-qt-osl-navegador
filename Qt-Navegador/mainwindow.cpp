#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    browser_ = new WebBrowser;
    setCentralWidget(browser_);

    mainMenu_ = new QMenuBar(this);
    mnuArchivo_ = new QMenu(tr("&Archivo"), this);
    mainMenu_ -> addMenu(mnuArchivo_);

    setMenuBar(mainMenu_);

    actArchivoSalir_ = new QAction(tr("&Salir"), this);
    mnuArchivo_ -> addAction(actArchivoSalir_);
    actArchivoSalir_ -> setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q));

    mnuMarcadores_ = new QMenu(tr("&Marcadores"), this);
    mainMenu_ -> addMenu(mnuMarcadores_);

    actMarcadoresHistorialEditar_ = new QAction(tr("&Editar marcadores"), this);
    mnuMarcadores_ -> addAction(actMarcadoresHistorialEditar_);

    actMarcadoresNuevo_ = new QAction(tr("&Nuevo marcador"), this);
    mnuMarcadores_ -> addAction(actMarcadoresNuevo_);
    actMarcadoresNuevo_ -> setShortcut(QKeySequence(Qt::CTRL + Qt::Key_D));

    actMarcadoresHome_ = new QAction(tr("&Cambiar Home Page"), this);
    mnuMarcadores_ -> addAction(actMarcadoresHome_);

    showMarcadores();
    showHistorial();

    connect(actArchivoSalir_, SIGNAL(triggered()), this, SLOT(close()));
    connect(actMarcadoresNuevo_, SIGNAL(triggered()), this, SLOT(setNuevoMarcador()));
    connect(actMarcadoresHome_, SIGNAL(triggered()), this, SLOT(setHomePageW()));

    connect(actMarcadoresHistorialEditar_, SIGNAL(triggered()), this, SLOT(editHistorial()));



}

MainWindow::~MainWindow()
{

}

void MainWindow::setNuevoMarcador () {
    QMessageBox::about(this, tr("Marcadores"),
                 tr("La página actual se añadió a marcadores."));
    QFile file("marcadores.txt");
    if (!file.open(QIODevice::Append | QIODevice::Text))
    return;

    QTextStream out(&file);
    out << browser_->getAddress()->text() << "\n";
    file.close();
}

void MainWindow::showMarcadores () {
    QFile file("marcadores.txt");
    file.open(QIODevice::ReadOnly | QIODevice::Text);

    QTextStream in(&file);
    QString linea = in.readLine();
    QAction *tmpAction = new QAction(linea.left(25), this);
    mnuMostrarMarcadores_ = mnuMarcadores_->addMenu(tr("Mis marcadores"));
    mnuMostrarMarcadores_ -> addAction(tmpAction);
    actMarcadoresLista_.append(tmpAction);
    connect(tmpAction, SIGNAL(triggered()), this, SLOT(setActualMarcador()));
    while (!in.atEnd()) {
        linea = in.readLine();
        tmpAction = new QAction(linea.left(25), this);
        tmpAction->setData(linea);
        mnuMostrarMarcadores_ -> addAction(tmpAction);
        actMarcadoresLista_.append(tmpAction);
        connect(tmpAction, SIGNAL(triggered()), this, SLOT(setActualMarcador()));
    }
    file.close();
}


void MainWindow::setActualMarcador() {
    browser_->setAddress(((QAction*)QObject::sender())->data().toString());
}

void MainWindow::setHomePageW() {
    browser_->setHomePage();
}

void MainWindow::showHistorial () {
    QFile file("historial.txt");
    file.open(QIODevice::ReadOnly | QIODevice::Text);

    QTextStream in(&file);
    QString linea = in.readLine();
    QAction *tmpAction = new QAction(linea.left(25), this);
    mnuMostrarHistorial_ = mnuMarcadores_->addMenu(tr("Mi historial"));
    mnuMostrarHistorial_ -> addAction(tmpAction);
    actMarcadoresLista_.append(tmpAction);
    connect(tmpAction, SIGNAL(triggered()), this, SLOT(setActualMarcador()));
    while (!in.atEnd()) {
        linea = in.readLine();
        tmpAction = new QAction(linea.left(25), this);
        tmpAction->setData(linea);
        mnuMostrarHistorial_ -> addAction(tmpAction);
        actMarcadoresLista_.append(tmpAction);
        connect(tmpAction, SIGNAL(triggered()), this, SLOT(setActualMarcador()));
    }
    file.close();
}


void MainWindow::editHistorial () {
    editarHistorial hist;
    hist.setGeometry(this->window()->x() + 50, this->window()->y() + 20, 200, 200);
    hist.setWindowTitle(tr("Editar marcadores"));

    hist.exec();
}
