#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //this->setContextMenuPolicy(Qt::CustomContextMenu);
    //connect(this, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(ShowContextMenu(const QPoint&)));


    //browser_ = new WebBrowser;

    this->setGeometry(0,0,800,600);
    tabs_ = new QTabWidget(this);
    tabs_->setTabsClosable(true);

    crearMenu();
    crearPestana();
    activateTab(0);

    // Centrar ventana en pantalla
    QRect qr = this->frameGeometry();
    qr.moveCenter(QDesktopWidget().availableGeometry().center());
    //tabs_->setMovable(true);

    tabs_->move(qr.topLeft());

    connect(tabs_, SIGNAL(tabCloseRequested(int)), this, SLOT(cerrarPestana(int)));

    mostrarBotonMas();

    connect(tabs_, SIGNAL(currentChanged(int)), SLOT(activateTab(int)));

    connect(tabs_, SIGNAL(tabBarDoubleClicked(int)), this, SLOT(cerrarPestana(int)));



}

MainWindow::~MainWindow()
{

}


void MainWindow::activateTab(int index) {
    qDebug("%d tab selected", index);
    pestanaActual_ = index;
}

void MainWindow::resizeEvent(QResizeEvent* event) {
    tabs_->setGeometry(this->geometry());
}

void MainWindow::setNuevoMarcador () {
    QMessageBox::about(this, tr("Marcadores"),
                 tr("La página actual se añadió a marcadores."));
    QFile file("marcadores.txt");
    if (!file.open(QIODevice::Append | QIODevice::Text))
    return;

    QTextStream out(&file);
    //out << browser_->getAddress()->text() << "\n";
    out << browserList_.at(pestanaActual_)->getAddress()->text() << "\n";
    file.close();

    mnuMarcadores_->clear();
    crearMenu();
}

void MainWindow::showMarcadores () {
    actMarcadoresNuevo_ = new QAction(tr("&Nuevo marcador"), this);
    mnuMarcadores_ -> addAction(actMarcadoresNuevo_);
    actMarcadoresNuevo_ -> setShortcut(QKeySequence(Qt::CTRL + Qt::Key_D));

    actMarcadoresHome_ = new QAction(tr("&Cambiar Home Page"), this);
    mnuMarcadores_ -> addAction(actMarcadoresHome_);

    mnuMostrarMarcadores_ = mnuMarcadores_->addMenu(tr("Mis marcadores"));

    QFile file("marcadores.txt");
    file.open(QIODevice::ReadOnly | QIODevice::Text);

    QTextStream in(&file);
    QString linea = in.readLine();
    QAction *tmpAction = new QAction(linea.left(35), this);
    mnuMostrarMarcadores_ -> addAction(tmpAction);
    connect(tmpAction, SIGNAL(triggered()), this, SLOT(setActualMarcador()));
    while (!in.atEnd()) {
        linea = in.readLine();
        tmpAction = new QAction(linea.left(35), this);
        tmpAction->setData(linea);
        mnuMostrarMarcadores_ -> addAction(tmpAction);
        connect(tmpAction, SIGNAL(triggered()), this, SLOT(setActualMarcador()));
    }
    file.close();
}


void MainWindow::setActualMarcador() {
    //browser_->setAddress(((QAction*)QObject::sender())->data().toString());
    browserList_.at(pestanaActual_)->setAddress(((QAction*)QObject::sender())->data().toString());
}

void MainWindow::setHomePageW() {
   // browser_->setHomePage();
    browserList_.at(pestanaActual_)->setHomePage();
}

void MainWindow::showHistorial () {
    actHistorialEditar_ = new QAction(tr("&Editar historial"), this);
    mnuHistorial_ -> addAction(actHistorialEditar_);

    actHistorialBorrar_ = new QAction(tr("&Borrar historial"), this);
    mnuHistorial_ -> addAction(actHistorialBorrar_);


    QFile file("historial.txt");
    file.open(QIODevice::ReadOnly | QIODevice::Text);

    QTextStream in(&file);
    QString linea = in.readLine();
    QAction *tmpAction = new QAction(linea.left(35), this);
    mnuMostrarHistorial_ = mnuHistorial_->addMenu(tr("Mi historial"));
    mnuMostrarHistorial_ -> addAction(tmpAction);
    connect(tmpAction, SIGNAL(triggered()), this, SLOT(setActualMarcador()));
    int cont = 0;
    while (!in.atEnd() && cont < 50) {
        cont++;
        linea = in.readLine();
        tmpAction = new QAction(linea.left(35), this);
        tmpAction->setData(linea);
        mnuMostrarHistorial_ -> addAction(tmpAction);
        connect(tmpAction, SIGNAL(triggered()), this, SLOT(setActualMarcador()));
    }
    file.close();
}

void MainWindow::borrarHistorial () {
    QFile file("historial.txt");
    file.open(QIODevice::Truncate | QIODevice::Text | QIODevice::ReadWrite);
    file.close();
    crearMenu();
}


void MainWindow::editHistorial () {
    editarHistorial hist;
    hist.setGeometry(this->window()->x() + 50, this->window()->y() + 20, 200, 200);
    hist.setWindowTitle(tr("Editar marcadores"));
    hist.exec();
}

void MainWindow::menuPestanas () {
    actPestanasNueva_ = new QAction(tr("&Nueva pestañas"), this);
    mnuPestanas_ -> addAction(actPestanasNueva_);
    actPestanasNueva_ -> setShortcut(QKeySequence(Qt::CTRL + Qt::Key_T));
    connect(actPestanasNueva_, SIGNAL(triggered()), this, SLOT(crearPestana()));


    actPestanasCerrar_ = new QAction(tr("&Cerrar pestaña actual"), this);
    mnuPestanas_ -> addAction(actPestanasCerrar_);
    actPestanasCerrar_ -> setShortcut(QKeySequence(Qt::CTRL + Qt::Key_W));
    connect(actPestanasCerrar_, SIGNAL(triggered()), this, SLOT(llamarCerrarPestana()));

}

void MainWindow::menuSesion () {
    actSesionRestaurar_ = new QAction(tr("&Restaurar sesión"), this);
    mnuSesion_ -> addAction(actSesionRestaurar_);
    connect(actSesionRestaurar_, SIGNAL(triggered()), this, SLOT(restaurarSesion()));
}

void MainWindow::restaurarSesion () {
    QFile file("sesion.txt");
    file.open(QIODevice::ReadOnly | QIODevice::Text);

    QTextStream in(&file);
    QString linea = in.readLine();
    if (linea != "") {
        browserList_.append(new WebBrowser);
        browserList_.last()->setAddress(linea);
        tabs_->addTab(browserList_.last(),browserList_.last()->getAddress()->text().left(25));
        while (!in.atEnd()) {
            linea = in.readLine();
            browserList_.append(new WebBrowser);
            browserList_.last()->setAddress(linea);
            tabs_->addTab(browserList_.last(),browserList_.last()->getAddress()->text().left(25));
        }
    }
    else {
    }
}


void MainWindow::crearPestana() {
  //  WebBrowser* browser_2 = new WebBrowser;
    browserList_.append(new WebBrowser);
    qDebug("%d browser list size", browserList_.size());
    tabs_->addTab(browserList_.last(),browserList_.last()->getAddress()->text().left(25));
}

void MainWindow::llamarCerrarPestana () {
    tabs_->tabCloseRequested(pestanaActual_);

}

void MainWindow::cerrarPestana(const int& index) {
    if (index == -1) {
        return;
    }

    browserList_.removeAt(pestanaActual_);

    qDebug("%d browser list size", browserList_.size());

    QWidget* tabItem = tabs_->widget(index);
    tabs_->removeTab(index);

    if (tabs_->count() <= 0) {
        QFile file("sesion.txt");
        file.open(QIODevice::Truncate | QIODevice::Text | QIODevice::ReadWrite);
        file.close();
        this->close();
    }

    delete(tabItem);
}


void MainWindow::crearMenu () {
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

    mnuPestanas_ = new QMenu(tr("&Pestañas"), this);
    mainMenu_ -> addMenu(mnuPestanas_);

    mnuSesion_ = new QMenu(tr("&Sesion"), this);
    mainMenu_ -> addMenu(mnuSesion_);


    showMarcadores();
    showHistorial();
    menuPestanas();
    menuSesion();

    //connect(actArchivoSalir_, SIGNAL(triggered()), this, SLOT(close()));
    connect(actArchivoSalir_, SIGNAL(triggered()), this, SLOT(cerarVentana()));
    connect(actMarcadoresNuevo_, SIGNAL(triggered()), this, SLOT(setNuevoMarcador()));
    connect(actMarcadoresHome_, SIGNAL(triggered()), this, SLOT(setHomePageW()));

    connect(actHistorialEditar_, SIGNAL(triggered()), this, SLOT(editHistorial()));
    connect(actHistorialBorrar_, SIGNAL(triggered()), this, SLOT(borrarHistorial()));
}

void MainWindow::cerarVentana () {
    if (browserList_.size() > 1) {

        QMessageBox* msgBox = new QMessageBox(this);
        msgBox->setText(tr("Tiene varias pestañas abiertas ¿desea cerrarlas?"));
        QPushButton *guardar = msgBox->addButton(tr("Guardar y salir"), QMessageBox::ActionRole);
        QPushButton *aceptar = msgBox->addButton(tr("Aceptar"), QMessageBox::ActionRole);
        QPushButton *cancelar = msgBox->addButton(tr("Cancelar"), QMessageBox::ActionRole);

        msgBox->exec();

        if (msgBox->clickedButton() == aceptar) {
            QFile file("sesion.txt");
            file.open(QIODevice::Truncate | QIODevice::Text | QIODevice::ReadWrite);
            file.close();
            this->close();
         }
         else if (msgBox->clickedButton() == guardar) {
             QFile file("sesion.txt");
             file.open(QIODevice::WriteOnly | QIODevice::Text);

             QTextStream out(&file);
             WebBrowser* pagina;
             foreach (pagina, browserList_) {
                 out << pagina->getAddress()->text() << endl;
             }
             file.close();
             this->close();
         }
         else if (msgBox->clickedButton() == cancelar) {
             // abort
         }
    }
    else {
        QFile file("sesion.txt");
        file.open(QIODevice::Truncate | QIODevice::Text | QIODevice::ReadWrite);
        file.close();
        this->close();
    }
}

void MainWindow::mostrarBotonMas () {
    QToolButton *newTabButton = new QToolButton(this);
    tabs_->setCornerWidget(newTabButton, Qt::TopRightCorner);
    newTabButton->setCursor(Qt::ArrowCursor);
    newTabButton->setAutoRaise(true);
    newTabButton->setIcon(QIcon(":/icons/resources/add.png"));
    QObject::connect(newTabButton, SIGNAL(clicked()), this, SLOT(crearPestana()));
    newTabButton->setToolTip(tr("Nueva pestaña"));
}
