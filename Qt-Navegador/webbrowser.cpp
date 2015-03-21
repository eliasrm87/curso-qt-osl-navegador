#include "webbrowser.h"

WebBrowser::WebBrowser(QWidget *parent) :
    QWidget(parent)
{
    mainMenu_ = new QMenuBar(this);
    mnuArchivo_ = new QMenu(tr("&Archivo"), this);
    mainMenu_->addMenu(mnuArchivo_);

    actArchivoHome_ = new QAction(tr("&Definir Home"), this);
    mnuArchivo_->addAction(actArchivoHome_);

    actArchivoSalir_ = new QAction(tr("&Salir"), this);
    actArchivoSalir_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q));
    actArchivoSalir_->setIcon(QIcon(":/iconos/iconos/exit.png"));
    mnuArchivo_->addAction(actArchivoSalir_);

    mnuMarcadores_ = new QMenu(tr("&Marcadores"), this);
    mainMenu_->addMenu(mnuMarcadores_);

    mnuHistorial_ = new QMenu(tr("&Historial"), this);
    mainMenu_->addMenu(mnuHistorial_);

    mnuHistorial_->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(mnuHistorial_,SIGNAL(customContextMenuRequested(QAction*)),this,\
            SLOT(contextMenuRequested(QAction*)));

    QFile Historial("historial.txt");
    Historial.open(QIODevice::ReadWrite | QIODevice::Text);
    while(!Historial.atEnd()) {
        QString tmp = Historial.readLine();
        actGoogle_ = new QAction(tmp, this);
        connect(actGoogle_,SIGNAL(triggered()),this,SLOT(onBookmark()));
        mnuHistorial_->addAction(actGoogle_);
    }
    Historial.close();

    QFile Archivo("marcadores.txt");
    Archivo.open(QIODevice::ReadWrite | QIODevice::Text);

    while(!Archivo.atEnd()) {
        QString tmp = Archivo.readLine();
        actGoogle_ = new QAction(tmp, this);
        connect(actGoogle_,SIGNAL(triggered()),this,SLOT(onBookmark()));
        mnuMarcadores_->addAction(actGoogle_);
    }
    Archivo.close();

    web_ = new QWebView(this);
    address_ = new QLineEdit(this);
    refresh_ = new QToolButton(this);
    back_ = new QToolButton(this);
    forward_ = new QToolButton(this);
    home_ = new QToolButton(this);
    addBookmark_ = new QToolButton(this);
    zoom_ = new QToolButton(this);
    zoomin_ = new QToolButton(this);
    zoomout_ = new QToolButton(this);
    add_ = new QToolButton(this);
    layout_ = new QGridLayout(this);
    refresh_->setIcon(QIcon(QPixmap(":/icons/resources/refresh.png")));
    back_->setIcon(QIcon(QPixmap(":/icons/resources/go-previous.png")));
    forward_->setIcon(QIcon(QPixmap(":/icons/resources/go-next.png")));
    home_->setIcon(QIcon(QPixmap(":/icons/resources/go-home.png")));
    addBookmark_->setIcon(QIcon(QPixmap(":/icons/resources/bookmark.png")));
    zoom_->setIcon(QIcon(QPixmap(":/icons/resources/expand.png")));
    zoomin_->setIcon(QIcon(QPixmap(":/icons/resources/zoom_in.png")));
    zoomout_->setIcon(QIcon(QPixmap(":/icons/resources/zoom_out.png")));
    add_->setIcon(QIcon(QPixmap(":/icons/resources/add.png")));
    layout_->addWidget(mainMenu_,0,0,1,9);
    layout_->addWidget(back_,1,0,1,1);
    layout_->addWidget(forward_,1,1,1,1);
    layout_->addWidget(home_,1,2,1,1);
    layout_->addWidget(refresh_,1,3,1,1);
    layout_->addWidget(addBookmark_,1,4,1,1);
    layout_->addWidget(address_,1,5,1,1);
    layout_->addWidget(add_,1,6,1,1);
    layout_->addWidget(zoom_,1,7,1,1);
    layout_->addWidget(zoomin_,1,8,1,1);
    layout_->addWidget(zoomout_,1,9,1,1);

    homepage_="http://www.google.com";
    getHome();
    address_->setText(homepage_);
    web_->load(homepage_);

    //meto la ventanita en el tab
    tab_ = new QTabWidget();
    tab_->addTab(web_,homepage_);
    tab_->setTabsClosable(true);
    tabi_= tab_->tabBar();
    layout_->addWidget(tab_,2,0,1,9);

    setLayout(layout_);
    setupConnections();
}

void WebBrowser::contextMenuRequested(QAction *d)
{
    mnuHistorial_->removeAction(d);
}

void WebBrowser::setupConnections()
{
    connect(addBookmark_,SIGNAL(pressed()),this,SLOT(onAddBMark()));
    connect(address_,SIGNAL(returnPressed()),this,SLOT(onLoad()));
    connect(actArchivoHome_,SIGNAL(triggered()),this,SLOT(onDefinirHome()));
    connect(actArchivoSalir_,SIGNAL(triggered()),this,SLOT(onQuit()));
    connect(refresh_,SIGNAL(pressed()),web_,SLOT(reload()));
    connect(forward_,SIGNAL(pressed()),web_,SLOT(forward()));
    connect(back_,SIGNAL(pressed()),web_,SLOT(back()));
    connect(home_,SIGNAL(pressed()),this,SLOT(onHome()));
    connect(web_,SIGNAL(urlChanged(QUrl)),this,SLOT(onUrlChange(QUrl)));
    connect(web_,SIGNAL(loadFinished(bool)),this,SLOT(onLoadFinished(bool)));
    connect(zoom_,SIGNAL(pressed()), this, SLOT(onOriginal()));
    connect(zoomin_,SIGNAL(pressed()), this, SLOT(onAmpliar()));
    connect(zoomout_,SIGNAL(pressed()), this, SLOT(onReducir()));
    connect(add_,SIGNAL(pressed()), this, SLOT(nueva_ventana()));
}

void WebBrowser::onLoad()
{

    if(!address_->text().startsWith("http://")
            && !address_->text().startsWith("https://")
            && address_->text().length()!=0){
        web_->load("http://"+address_->text());
    }
    else{
        web_->load(address_->text());
    }
}

void WebBrowser::getHome(){
    QFile Archivo("homepage.txt");
    Archivo.open(QIODevice::ReadWrite | QIODevice::Text);
    QString tmp = Archivo.readLine();
    homepage_=tmp.split(QRegExp("\n|\r\n|\r"))[0];
    Archivo.close();
}

void WebBrowser::onDefinirHome(){
    bool ok;
    QString text = QInputDialog::getText(this, tr("New Home Page"),tr("Direccion:"), QLineEdit::Normal,"", &ok);
    if (ok){
       homepage_ = text;
       QFile fileHome("homepage.txt");
       fileHome.open(QIODevice::WriteOnly);
       QTextStream out(&fileHome);
       out << homepage_ << endl;
       fileHome.close();
    }
}

void WebBrowser::onQuit()
{
    QApplication::quit();
}

void WebBrowser::onAmpliar () {
    web_->setZoomFactor( web_->zoomFactor() + 0.2);
}

void WebBrowser::onReducir () {
    web_->setZoomFactor( web_->zoomFactor() - 0.2);
}

void WebBrowser::onOriginal () {
    web_->setZoomFactor(1);
}

void WebBrowser::onAddBMark()
{
    QFile Archivo("marcadores.txt");
    Archivo.open(QIODevice::Append | QIODevice::Text);
    QTextStream stream( &Archivo );
    stream << address_->text() << endl;
    actGoogle_ = new QAction(address_->text(), this);
    connect(actGoogle_,SIGNAL(triggered()),this,SLOT(onBookmark()));
    mnuMarcadores_->addAction(actGoogle_);
    Archivo.close();
}

void WebBrowser::onHome()
{
    web_->load(homepage_);
}

void WebBrowser::onUrlChange(QUrl url)
{
    address_->setText(url.toString());
    QFile Archivo("historial.txt");
    Archivo.open(QIODevice::Append | QIODevice::Text);
    QTextStream stream( &Archivo );
    stream << url.toString().split(QRegExp("\n|\r\n|\r"))[0] << endl;
    Archivo.close();
    actGoogle_ = new QAction(url.toString().split(QRegExp("\n|\r\n|\r"))[0], this);
    connect(actGoogle_,SIGNAL(triggered()),this,SLOT(onBookmark()));
    mnuHistorial_->addAction(actGoogle_);
    tab_->setTabText(0, url.toString().split(QRegExp("\n|\r\n|\r"))[0]);
}

void WebBrowser::onLoadFinished(bool ok)
{
    if(!ok){
        web_->load("http://google.com/?q="+address_->text());
    }
}

void WebBrowser::onBookmark()
{
    web_->load(((QAction*) QObject::sender())->text().split(QRegExp("\n|\r\n|\r"))[0]);
}

void WebBrowser::nueva_ventana() { 
    tab_->addTab(new QWidget,"Nueva Ventana");
    //tab_->resize(1,1);
//    cerrar_ = new QPushButton(this);
//    cerrar_->setText("X");
//    cerrar_->setStyleSheet("border:none");
//    tabi_->setTabButton(tabi_->count() -1, QTabBar::RightSide,cerrar_);
//    connect(cerrar_,SIGNAL(clicked()), this, SLOT(cerrar_nueva_ventana()));

}

void WebBrowser::cerrar_nueva_ventana(){
    tab_->close();
}
