#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    browser_ = new WebBrowser;
    setCentralWidget(browser_);

    mainMenu_ = new QMenuBar(this);

    mnuMarcadores_ = new QMenu(tr("&Marcadores"),this);
    mainMenu_->addMenu(mnuMarcadores_);
    setMenuBar(mainMenu_);

    QFile archivo;

    archivo.setFileName("home.txt");
    if(archivo.open(QFile::ReadOnly))
    {
        while(!archivo.atEnd())
        {
            mnuMarcadores_->addAction(archivo.readLine());
        }

        archivo.close();
    }


    connect(browser_ ,SIGNAL(signalMarcador(QString)),this,SLOT(capturadorMarcador(QString)));
}

MainWindow::~MainWindow()
{

}

void MainWindow::capturadorMarcador(QString url)
{
    QAction* act = mnuMarcadores_->addAction(url);
    connect(act, SIGNAL(triggered()), this, SLOT(marcadorPulsado()));
    QFile archivo;
    archivo.setFileName("home.txt");
    if(archivo.open(QFile::WriteOnly|QFile::Append))
    {
        QTextStream out(&archivo);
        out<<url<<endl;
        archivo.close();
    }

}

void MainWindow::marcadorPulsado()
{
    browser_->goTo(((QAction*)QObject::sender())->text());
}
