#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    browser_ = new WebBrowser;
    setCentralWidget(browser_);

    venta_ = new QToolButton;
    layout_ = new QGridLayout;
    layout_->addWidget(venta_,0,4,1,1);
    venta_->setText("Boton");
    connect(venta_, SIGNAL(pressed()),this,SLOT(new_win()));


    this->setWindowTitle(tr("NAVEGADOR"));
    mainMenu_= new QMenuBar(this);
    mnuArchivo_= new QMenu(tr("&Archivo"),this);
    mainMenu_->addMenu(mnuArchivo_);
    setMenuBar(mainMenu_);

    actArchivoSalir_ = new QAction(QIcon(":/icons/resources/Button-Close-icon.png"),tr("&Salir"),this);
    actArchivoSalir_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_S));
    mnuArchivo_->addAction(actArchivoSalir_);
    connect(actArchivoSalir_, SIGNAL(triggered()),this,SLOT(Salir()));

    mnuAyuda_ = new QMenu(tr("A&yuda"),this);
    mainMenu_->addMenu(mnuAyuda_);
    actAyudaAcerca_ = new QAction(tr("Acerca de"),this);
    mnuAyuda_->addAction(actAyudaAcerca_);
    connect(actAyudaAcerca_, SIGNAL(triggered()),this,SLOT(alAcercaDe()));
}

void MainWindow::Salir()
{
    QMessageBox msg(this);
    msg.setText("<center>¿Salir?</center>");
    msg.addButton("Si",QMessageBox::YesRole);
    msg.addButton("No",QMessageBox::NoRole);
    if (!msg.exec())
        close();
}

void MainWindow::alAcercaDe()
{
    QMessageBox msg(this);
    msg.setWindowTitle(tr("Acerca de"));
    msg.setText("<p>WebBrowser's Aaron (in Qt!)</p><p>v 1.0</p>");
    msg.addButton("Aceptar",QMessageBox::AcceptRole);

    if (msg.exec())
        close();
}

void MainWindow::new_win()
{
    base_=new QWebView();
    base_->load(QUrl ("http://www.youtube.com/"));
    base_->show();
    caja_=new QVBoxLayout();
    caja_->insertWidget(0,base_,0,Qt::AlignBottom);
    ventana_=new QTabWidget();
    ventana_->setLayout(caja_);
    ventana_->addTab(new QWidget,"New");
    tab_= ventana_->tabBar();
    salir_=new QPushButton();
    salir_->setText("x");
    tab_->setTabButton(tab_->count()-1,QTabBar::RightSide,salir_);
    layout_->addWidget(ventana_,1,0,1,1);
    connect(salir_,SIGNAL(pressed()),this,SLOT(cerrar2()));
}

void MainWindow::cerrar2()
{
    ventana_->close();
}

MainWindow::~MainWindow()
{
    mainMenu_->deleteLater();
    mnuArchivo_->deleteLater();
    actArchivoSalir_->deleteLater();
}

