#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //Establecemos el tamaño inicial de la ventana
    this->setGeometry(30, 30, 800, 600);

    //Establecemos el título de la ventana
    this->setWindowTitle(tr("Navegador"));


    browser_ = new WebBrowser(this);

    //Se coloca en el centro de la ventana principal nuestro navegador.
    setCentralWidget(browser_);

    //Inicializamos los menús
    mainMenu_ = new QMenuBar(this);

    //Coloca la barra de menú correctamente.
    setMenuBar(mainMenu_);

    mnuMarcadores_ = new QMenu(tr("&Marcadores"), this);
    //Se añade la opción Marcadores a la barra de menú.
    mainMenu_->addMenu(mnuMarcadores_);


    //Se leen todos los favoritos del archivo de marcadores y se añande al menú
    // de marcadores.
    QFile FileMarcadores_;
    FileMarcadores_.setFileName("Marcadores.txt");

    if (FileMarcadores_.open(QFile::ReadOnly))
    {
        QTextStream InterfaceFileMarcadores_(&FileMarcadores_);

        while(!InterfaceFileMarcadores_.atEnd())
        {
            //Acción Marcador de menú Marcadores.
            //QAction* actMarcadorMarcadores_;

            //actMarcadorMarcadores_ = new QAction(InterfaceFileMarcadores_.device()->readLine(), this);

            //Se añade el marcador como una acción al Menú de marcadores.
            QAction *actMarcador_ = mnuMarcadores_->addAction(InterfaceFileMarcadores_.readLine());

            //Al pulsar sobre el marcador que se acaba de añadir se invocará la función
            // "onMarcador()"
            connect(actMarcador_, SIGNAL(triggered()), this, SLOT(onMarcador()));
        }

        FileMarcadores_.close();
    }

    //Se estable que "mainwindow" capture la señal "signalAnadirMarcador" emitida por browser_,
    // y que el slot "onCapturarSignalAñadirMarcador" maneje dicha señal.
    connect(browser_, SIGNAL(signalAnadirMarcador(QString)), this, SLOT(onCapturarSignalAnadirMarcador(QString)));

}

MainWindow::~MainWindow()
{

}

//Método que maneja la señal "signalAnadirMarcador(QString)" de browser_, tal
// y como se indicó en el connect del constructor.
//Recibe la url actual de browser_ y se añade al menú de marcadores.
void MainWindow::onCapturarSignalAnadirMarcador(QString URL)
{
    QAction *actMarcador_ = mnuMarcadores_->addAction(URL);

    //Al pulsar sobre el marcador que se acaba de añadir se invocará la función
    // "onMarcador()"
    connect(actMarcador_, SIGNAL(triggered()), this, SLOT(onMarcador()));


    //Se añade el marcador al fichero.
    QFile FileMarcadores_;
    FileMarcadores_.setFileName("Marcadores.txt");

    if (FileMarcadores_.open(QFile::Append))
    {
            QTextStream InterfaceFileMarcadores_(&FileMarcadores_);
            InterfaceFileMarcadores_<< URL << endl;

            FileMarcadores_.close();
    }
}


//Esta función se invoca cuando se pincha en alguno de los marcadores.
//Se carga la url del marcador en el navegador.
void MainWindow::onMarcador()
{
    //Como el objeto que invoca esta función es de tipo QAction hacemos un type cast
    // para recuperar su propiedad text que contiene la URL a la que se quiere navegar.

    browser_->goTo(((QAction*)QObject::sender())->text());
}




