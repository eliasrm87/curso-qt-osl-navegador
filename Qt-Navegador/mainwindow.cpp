#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    qDebug()<<"Constructor MainWindow";
    //Establecemos el tamaño inicial de la ventana
    this->setGeometry(30, 30, 800, 400);

    qDebug()<<"Estableciendo nombre de la ventana ...";
    this->setWindowTitle(tr("Navegador --"));

    qDebug()<<"Definiendo el WebBrowser...";
    browser_ = new WebBrowser;
    setCentralWidget(browser_);

    qDebug()<<"Definiciendo el Historial...";
    historial_ = new Record;

    qDebug()<<"Definiciendo el Marcador...";
    marcador_ = new Record("marcadores.txt");

    qDebug()<<"Restaurando del fichero configuración ...";
    readSettings();

    qDebug()<<"Cargando Navegador ...";
    browser_->load();

    qDebug()<<"Añadiendo elementos en la barra de menu ...";
    barraMenu();

    qDebug()<<"Conectando las conexiones ...";
    setupConnections();

    setMenuBar(mainMenu_);

    qDebug()<<"Instalando Filtro de eventos propios ...";
    installEventFilter(this);

}

void MainWindow::setupConnections()
{
    connect(actVerZoomPlus_, SIGNAL(triggered()), browser_, SLOT(AcercarZoom()));
    connect(actVerZoomLess_, SIGNAL(triggered()), browser_, SLOT(AlejarZoom()));
    connect(actHerramientasHomepage_, SIGNAL(triggered()),this, SLOT(homePage()));
    connect(actHerramientasConfig_, SIGNAL(triggered()),this, SLOT(eraseConfig()));
    connect(actHistorialBorrar_, SIGNAL(triggered()), this, SLOT(cleanRecord()));
    connect(browser_->getWeb(), SIGNAL(urlChanged(QUrl)), this, SLOT(toRecord())); //mantiene la recarga de la web
    connect(actMarcadoresAñadir_, SIGNAL(triggered()), this, SLOT(toMarcador()));
    connect(actMarcadoresBorrar_, SIGNAL(triggered()), this, SLOT(cleanMarcador()));
}

void MainWindow::barraMenu(){
    //Inicializamos los menús con sus opciones

    /*Barra de Menus*/
    mainMenu_ = new QMenuBar(this);

    /*Navegador*/
    mnuNavegador_ = new QMenu(tr("Navegador"), this);
    mainMenu_->addMenu(mnuNavegador_);

    /*Action Navegador*/


    /*Ver*/
    mnuVer_ = new QMenu(tr("Ver"), this);
    mainMenu_->addMenu(mnuVer_);

    /*Action Ver*/

    actVerZoomPlus_ = new QAction(tr("Acercar"), this);
    actVerZoomPlus_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Plus));
    mnuVer_->addAction(actVerZoomPlus_);

    actVerZoomLess_ = new QAction(tr("Alejar"), this);
    actVerZoomLess_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Minus));
    mnuVer_->addAction(actVerZoomLess_);

    /*Historial*/
    mnuHistorial_ = new QMenu(tr("Historial"), this);
    mnuVer_->addMenu(mnuHistorial_);

    /*Action Historial*/

    actHistorialBorrar_= new QAction(tr("Borrar Historial"), this);
    mnuHistorial_->addAction(actHistorialBorrar_);
    mnuHistorial_->addSeparator();

    /*Marcadores*/
    mnuMarcadores_ = new QMenu(tr("Marcadores"), this);
    mainMenu_->addMenu(mnuMarcadores_);

    /*Action Marcadores*/
    actMarcadoresAñadir_= new QAction(tr("Añadir a Marcadores"), this);
    mnuMarcadores_->addAction(actMarcadoresAñadir_);
    mnuMarcadores_->addSeparator();

    mnuVerMarcadores_ = new QMenu(tr("Marcadores"), this);
    mnuMarcadores_->addMenu(mnuVerMarcadores_);

    actMarcadoresBorrar_= new QAction(tr("Borrar Marcadores"), this);
    mnuVerMarcadores_->addAction(actMarcadoresBorrar_);
    mnuVerMarcadores_->addSeparator();

    /*Herramientas*/
    mnuHerramientas_ = new QMenu(tr("Herramientas"), this);
    mainMenu_->addMenu(mnuHerramientas_);

    /*Action Herramientas*/

    actHerramientasHomepage_ = new QAction(tr("Pagina Por Defecto"), this);
    mnuHerramientas_ -> addAction(actHerramientasHomepage_);

    actHerramientasConfig_ = new QAction(tr("Restablecer configuración"), this);
    mnuHerramientas_ -> addAction(actHerramientasConfig_);

}


void MainWindow::readSettings()
{
    qDebug()<<"Leyendo archivo de configuración.";
    QSettings settings_(QSettings::IniFormat, QSettings::UserScope, "Haniel", "Navegador--");
    settings_.beginGroup("MainWindow");
    qDebug()<<"Valor del homepage: "<<settings_.value("HomePage").toString();

    if(settings_.value("HomePage").toString() == "")
        browser_->set_homepage("https://duckduckgo.com");
    else
        browser_->set_homepage(settings_.value("HomePage").toString());
    settings_.endGroup();
}

void MainWindow::writeSettings()
{
    qDebug()<<"Escribiendo archivo de configuración.";
    //enviamos al constructor los parametors necesarios para que el fichero de configuracion sea .ini
    QSettings settings_(QSettings::IniFormat, QSettings::UserScope, "Haniel", "Navegador--");
    settings_.beginGroup("MainWindow");
    settings_.setValue("HomePage", browser_->get_homepage());
    settings_.endGroup();

}

void MainWindow::homePage()
{
    bool aceptar;

    qDebug()<<"dentro de home page";
    QString url = QInputDialog::getText(this, tr("Pagina por defecto"),
                                                  tr("Introduzca la URL:"),
                                                  QLineEdit::Normal,
                                                  browser_->get_homepage(),
                                                  &aceptar);
    QRegExp whiteSpaces("^\\s+$");

    if (aceptar && !url.isEmpty() && !whiteSpaces.exactMatch(url)) {
        browser_->set_homepage(url);
    }
}

void MainWindow::eraseConfig()
{
    QSettings settings_(QSettings::IniFormat, QSettings::UserScope, "Haniel", "Navegador--");
    QMessageBox sure;
    sure.setWindowTitle(tr("Aviso"));
    sure.setText(tr("Se reestableceran toda la configuración de fabrica. Y se reiniciara la aplicación."));
    sure.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    int ret = sure.exec();

    if (ret == QMessageBox::Ok){
        settings_.clear();
        slotReboot();
    }

}

void MainWindow::slotReboot()
{
    qDebug() << "Reiniciando Aplicacion ...";
    qApp->quit();
    QProcess::startDetached(qApp->arguments()[0], qApp->arguments());

}

void MainWindow::cleanRecord()
{
    historial_->eraseRecord();
}

void MainWindow::cleanMarcador()
{
    marcador_->eraseRecord();
    loadMarcador();
}

void MainWindow::toRecord()
{

    qDebug() << "To Record:"<<browser_->getAddress();
    historial_->addRecord(browser_->getAddress());
    loadRecord();
}

void MainWindow::loadWeb()
{
    QAction *accion = (QAction*)QObject::sender();
    browser_->setAddress(accion->text());
}

void MainWindow::loadRecord()
{
    QString url;
    for(qint16 i=0; i<5; i++){
        qDebug()<<historial_->readLine(i);
        url=historial_->readLine(i);
        if(url != ""){
            QAction *actGoUrl = new QAction(url, this);
            mnuHistorial_->addAction(actGoUrl);
            connect(actGoUrl, SIGNAL(triggered()), this, SLOT(toRecord()));
        }

    }
}

void MainWindow::loadMarcador()
{
    QString url;
    qint16 i=0;
    while(!marcador_->readLine(i).isEmpty()){
        qDebug()<<"To Marcador: "<<marcador_->readLine(i);
        url=marcador_->readLine(i);
        QAction *actGoUrlM = new QAction(url, this);
        mnuVerMarcadores_->addAction(actGoUrlM);
        connect(actGoUrlM, SIGNAL(triggered()), this, SLOT(loadWeb()));
        i++;
        qDebug()<<"I:"<<i;
    }
}
void MainWindow::toMarcador()
{
    qDebug() << "To Record Marcador:"<<browser_->getAddress();
    marcador_->addRecord(browser_->getAddress());
    loadMarcador();
}

bool MainWindow::alSalir(){
    QMessageBox sure;
    sure.setWindowTitle(tr("Aviso"));
    sure.setText(tr("¿Está seguro que desea salir?"));
    sure.setStandardButtons(QMessageBox::Ok | QMessageBox::Close);
    int ret = sure.exec();

    if (ret == QMessageBox::Ok)
        return true;

    return false;
}

MainWindow::~MainWindow()
{
    //Liberamos los recursos
    mainMenu_->deleteLater();
    browser_->deleteLater();
    mnuNavegador_->deleteLater();
    mnuMarcadores_->deleteLater();
    mnuHerramientas_->deleteLater();
    actHerramientasHomepage_->deleteLater();
    actHerramientasConfig_ ->deleteLater();
    mnuHistorial_->deleteLater();
    mnuVer_ ->deleteLater();
    actVerZoomPlus_ ->deleteLater();
    actVerZoomLess_->deleteLater();
    actionReboot->deleteLater();
    qApp->deleteLater();
}

bool MainWindow::eventFilter(QObject *object, QEvent *event)
{
    if (event->type() == QEvent::Close) {
        if (!alSalir())
            event->ignore();
        qDebug()<<"Dentro del exit Event Filter";
        writeSettings();
        historial_->eraseRecord(); //eliminamos el historial cada vez que salgamos, podriamos no ponerlo pero me gusta asi.
        return true;
    }
    return QMainWindow::eventFilter(object,event);
}
