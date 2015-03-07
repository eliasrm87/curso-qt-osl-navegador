#include "webbrowser.h"

WebBrowser::WebBrowser(QWidget *parent) :
    QWidget(parent)
{
    mainMenu_ = new QMenuBar(this);
    mnuArchivo_ = new QMenu(tr("&Archivo"), this);
    mainMenu_->addMenu(mnuArchivo_);

    actArchivoSalir_ = new QAction(tr("&Salir"), this);
    actArchivoSalir_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q));
    actArchivoSalir_->setIcon(QIcon(":/iconos/iconos/exit.png"));
    mnuArchivo_->addAction(actArchivoSalir_);

    mnuMarcadores_ = new QMenu(tr("&Marcadores"), this);

    QFile Historial("historial.txt");
    Historial.open(QIODevice::ReadWrite | QIODevice::Text);
    Historial.close();

    QFile Archivo("marcadores.txt");
    Archivo.open(QIODevice::ReadWrite | QIODevice::Text);

    mainMenu_->addMenu(mnuMarcadores_);

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
    layout_ = new QGridLayout(this);
    refresh_->setIcon(QIcon(QPixmap(":/icons/resources/refresh.png")));
    back_->setIcon(QIcon(QPixmap(":/icons/resources/go-previous.png")));
    forward_->setIcon(QIcon(QPixmap(":/icons/resources/go-next.png")));
    home_->setIcon(QIcon(QPixmap(":/icons/resources/go-home.png")));
    addBookmark_->setIcon(QIcon(QPixmap(":/icons/resources/bookmark.png")));
    layout_->addWidget(mainMenu_,0,0,1,6);
    layout_->addWidget(back_,1,0,1,1);
    layout_->addWidget(forward_,1,1,1,1);
    layout_->addWidget(home_,1,2,1,1);
    layout_->addWidget(refresh_,1,3,1,1);
    layout_->addWidget(addBookmark_,1,4,1,1);
    layout_->addWidget(address_,1,5,1,1);
    layout_->addWidget(web_,2,0,1,6);

    homepage_="http://www.google.com";
    address_->setText(homepage_);
    web_->load(homepage_);
    setLayout(layout_);
    setupConnections();
}

void WebBrowser::setupConnections()
{
    connect(addBookmark_,SIGNAL(pressed()),this,SLOT(onAddBMark()));
    connect(address_,SIGNAL(returnPressed()),this,SLOT(onLoad()));
    connect(actArchivoSalir_,SIGNAL(triggered()),this,SLOT(onQuit()));
    connect(refresh_,SIGNAL(pressed()),web_,SLOT(reload()));
    connect(forward_,SIGNAL(pressed()),web_,SLOT(forward()));
    connect(back_,SIGNAL(pressed()),web_,SLOT(back()));
    connect(home_,SIGNAL(pressed()),this,SLOT(onHome()));
    connect(web_,SIGNAL(urlChanged(QUrl)),this,SLOT(onUrlChange(QUrl)));
    connect(web_,SIGNAL(loadFinished(bool)),this,SLOT(onLoadFinished(bool)));
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

void WebBrowser::onQuit()
{
    QApplication::quit();
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

