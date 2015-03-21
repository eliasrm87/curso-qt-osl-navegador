#include "webbrowser.h"
#include <QDebug>

WebBrowser::WebBrowser(QWidget *parent) :
    QWidget(parent)
{
    web_ = new QWebView(this);
    address_ = new QLineEdit(this);
    refresh_ = new QToolButton(this);
    back_ = new QToolButton(this);
    forward_ = new QToolButton(this);
    home_ = new QToolButton(this);
    addbookmark_ = new QToolButton(this);
    layout_ = new QGridLayout(this);
    refresh_->setIcon(QIcon(QPixmap(":/icons/resources/refresh.png")));
    back_->setIcon(QIcon(QPixmap(":/icons/resources/go-previous.png")));
    forward_->setIcon(QIcon(QPixmap(":/icons/resources/go-next.png")));
    home_->setIcon(QIcon(QPixmap(":/icons/resources/go-home.png")));
    addbookmark_->setIcon(QIcon(QPixmap(":/icons/resources/bookmark.png")));

    //Inicializamos el menú (vacío)
    mainMenu_ = new QMenuBar(this);

    layout_->addWidget(mainMenu_,0,0,1,6);
    layout_->addWidget(back_,1,0,1,1);
    layout_->addWidget(forward_,1,1,1,1);
    layout_->addWidget(home_,1,2,1,1);
    layout_->addWidget(refresh_,1,3,1,1);
    layout_->addWidget(addbookmark_,1,4,1,1);
    layout_->addWidget(address_,1,5,1,1);
    layout_->addWidget(web_,2,0,1,6);
    homepage_="http://duckduckgo.com";
    address_->setText(homepage_);
    web_->load(homepage_);
    bookmarks_file_="bookmarks.txt";
    history_file_="historial.txt";
    setLayout(layout_);
    setupConnections();
    refreshBookmarks();
}

void WebBrowser::refreshBookmarks(){
    mainMenu_->clear();
    mnuBookmarks_ = new QMenu(tr("&Favoritos"), this);
    mainMenu_->addMenu(mnuBookmarks_);
    QFile Archivo(bookmarks_file_);
    QFile file( bookmarks_file_ );
    if ( file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        mainMenu_->addMenu(mnuBookmarks_);
        while(!file.atEnd()) {
            actmarcador_ = new QAction((file.readLine().split('\n')[0]), this);
            connect(actmarcador_,   SIGNAL(triggered()),    this,   SLOT(goToBookmark()));
            mnuBookmarks_->addAction(actmarcador_);
        }
    }
    Archivo.close();
}

void WebBrowser::setupConnections()
{
    connect(address_,       SIGNAL(returnPressed()),    this,   SLOT(onLoad()));
    connect(refresh_,       SIGNAL(pressed()),          web_,   SLOT(reload()));
    connect(forward_,       SIGNAL(pressed()),          web_,   SLOT(forward()));
    connect(back_,          SIGNAL(pressed()),          web_,   SLOT(back()));
    connect(home_,          SIGNAL(pressed()),          this,   SLOT(onHome()));
    connect(addbookmark_,   SIGNAL(pressed()),          this,   SLOT(addToBookmarks()));
    connect(web_,           SIGNAL(urlChanged(QUrl)),   this,   SLOT(onUrlChange(QUrl)));
    connect(web_,           SIGNAL(loadFinished(bool)), this,   SLOT(onLoadFinished(bool)));
}

void WebBrowser::goToBookmark()
{
    web_->load(((QAction*) QObject::sender())->text().split(QRegExp("\n|\r\n|\r"))[0]);
}

void WebBrowser::addToBookmarks()
{
    QFile file( bookmarks_file_ );
    if ( file.open(QIODevice::Append) ) {
        QTextStream stream( &file );
        stream << address_->text() << endl;
    }
    file.close();
    refreshBookmarks();
}

void WebBrowser::onLoad()
{
    if(!address_->text().startsWith("http://")
            && !address_->text().startsWith("https://")
            && address_->text().length()!=0) {
        web_->load("http://"+address_->text());
    } else {
        web_->load(address_->text());
    }
}

void WebBrowser::onHome()
{
    web_->load(homepage_);
}

void WebBrowser::onUrlChange(QUrl url)
{
    address_->setText(url.toString());
    QFile file( history_file_ );
    if ( file.open(QIODevice::Append) ) {
        QTextStream stream( &file );
        stream << address_->text() << endl;
    }
    file.close();
    refreshHistorial();
}

void WebBrowser::onLoadFinished(bool ok)
{
    if(!ok)
        web_->load("https://duckduckgo.com/?q="+address_->text());
}

