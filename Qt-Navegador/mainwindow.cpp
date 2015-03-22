/*
 *  Adrián Rodríguez Bazaga
 *  alu0100826456@ull.edu.es
 *  Navegador web - Curso de QT
 *
 * */

#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    browser_ = new WebBrowser(this);
    connect(browser_, SIGNAL(signalRB()), this, SLOT(refreshHistorial()));
    setCentralWidget(browser_);

    //Imp. clase
    setupMenu();

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

    //mnuMarcadores_->clear();
    refreshMarcadores();
}

void MainWindow::refreshMarcadores() {
    mnuMostrarMarcadores_->clear();

    QFile file("marcadores.txt");
    file.open(QIODevice::ReadOnly | QIODevice::Text);

    QTextStream in(&file);
    QString linea;
    QAction *tmpAction;
    while (!in.atEnd()) {
        linea = in.readLine();
        tmpAction = new QAction(linea.left(35), this);
        tmpAction->setData(linea);
        mnuMostrarMarcadores_ -> addAction(tmpAction);
        connect(tmpAction, SIGNAL(triggered()), this, SLOT(setActualMarcador()));
    }
    file.close();
}

void MainWindow::showMarcadores () {
    actMarcadoresNuevo_ = new QAction(tr("&Nuevo marcador"), this);
    mnuMarcadores_ -> addAction(actMarcadoresNuevo_);
    actMarcadoresNuevo_ -> setShortcut(QKeySequence(Qt::CTRL + Qt::Key_D));

    actMarcadoresHome_ = new QAction(tr("&Cambiar Pag Principal"), this);
    mnuMarcadores_ -> addAction(actMarcadoresHome_);

    mnuMostrarMarcadores_ = mnuMarcadores_->addMenu(tr("Mis marcadores"));

    QFile file("marcadores.txt");
    file.open(QIODevice::ReadOnly | QIODevice::Text);

    QTextStream in(&file);
    QString linea;
    QAction *tmpAction;
    while (!in.atEnd()) {
        linea = in.readLine();
        tmpAction = new QAction(linea.left(35), this);
        tmpAction->setData(linea);
        mnuMostrarMarcadores_ -> addAction(tmpAction);
        connect(tmpAction, SIGNAL(triggered()), this, SLOT(setActualMarcador()));
    }
    file.close();
}

void MainWindow::showHistorial () {

    QAction *tmpAction;

    mnuVerHistorial_ = mnuHistorial_->addMenu(tr("Ver"));
    //Limpiar historial
    tmpAction = new QAction("Limpiar", this);
    mnuHistorial_->addAction(tmpAction);
    connect(tmpAction, SIGNAL(triggered()), this, SLOT(limpiarHistorial())); //Aprovecho la función también para el historial
    //

    QFile file("historial.txt");
    file.open(QIODevice::ReadOnly | QIODevice::Text);

    QTextStream in(&file);
    QString linea;
    while (!in.atEnd()) {
        linea = in.readLine();
        tmpAction = new QAction(linea.left(35), this);
        tmpAction->setData(linea);
        mnuVerHistorial_ -> addAction(tmpAction);
        connect(tmpAction, SIGNAL(triggered()), this, SLOT(setActualMarcador())); //Aprovecho la función también para el historial
    }
    file.close();
}

void MainWindow::refreshHistorial() {
    mnuVerHistorial_->clear();

    QFile file("historial.txt");
    file.open(QIODevice::ReadOnly | QIODevice::Text);

    QTextStream in(&file);
    QString linea;
    QAction *tmpAction;
    while (!in.atEnd()) {
        linea = in.readLine();
        tmpAction = new QAction(linea.left(35), this);
        tmpAction->setData(linea);
        mnuVerHistorial_ -> addAction(tmpAction);
        connect(tmpAction, SIGNAL(triggered()), this, SLOT(setActualMarcador())); //Aprovecho la función también para el historial
    }
    file.close();
}

void MainWindow::limpiarHistorial() {
    QFile file("historial.txt");
    file.remove();
    file.close();
    refreshHistorial();
}


void MainWindow::setActualMarcador() {
    browser_->setAddress(((QAction*)QObject::sender())->data().toString());
}

void MainWindow::setPagPrincipal() {
    browser_->setHomePage();
}

void MainWindow::setupMenu () {
    mainMenu_ = new QMenuBar(this);
    mnuArchivo_ = new QMenu(tr("&Archivo"), this);
    mainMenu_ -> addMenu(mnuArchivo_);

    setMenuBar(mainMenu_);

    actArchivoSalir_ = new QAction(tr("&Salir"), this);
    mnuArchivo_ -> addAction(actArchivoSalir_);
    actArchivoSalir_ -> setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q));

    mnuMarcadores_ = new QMenu(tr("&Marcadores"), this);
    mainMenu_ -> addMenu(mnuMarcadores_);

    mnuHistorial_ = new QMenu(tr("&Historial"), this);
    mainMenu_ -> addMenu(mnuHistorial_);

    showMarcadores();
    showHistorial();

    connect(actArchivoSalir_, SIGNAL(triggered()), this, SLOT(close()));
    connect(actMarcadoresNuevo_, SIGNAL(triggered()), this, SLOT(setNuevoMarcador()));
    connect(actMarcadoresHome_, SIGNAL(triggered()), this, SLOT(setPagPrincipal()));

}
