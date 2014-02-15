#include "webbrowser.h"

WebBrowser::WebBrowser(QWidget *parent) :
    QWidget(parent)
{
    web_ = new QWebView;
    address_ = new QLineEdit;
    refresh_ = new QToolButton;
    back_ = new QToolButton;
    forward_ = new QToolButton;
    home_ = new QToolButton;
    bookmarks_ = new QToolButton;
    books = new bookmarks();
    layout_ = new QGridLayout;

    //Cargamos los iconos para los botones
    refresh_->setIcon(QIcon(QPixmap(":/icons/resources/refresh.png")));
    back_->setIcon(QIcon(QPixmap(":/icons/resources/go-previous.png")));
    forward_->setIcon(QIcon(QPixmap(":/icons/resources/go-next.png")));
    home_->setIcon(QIcon(QPixmap(":/icons/resources/go-home.png")));
    bookmarks_->setIcon(QIcon(QPixmap(":/icons/resources/bookmarks.png")));

    //Elemento,(posicion inicial), filas, columnas
    layout_->addWidget(back_,0,0,1,1);
    layout_->addWidget(forward_,0,1,1,1);
    layout_->addWidget(home_,0,2,1,1);
    layout_->addWidget(refresh_,0,3,1,1);
    layout_->addWidget(bookmarks_,0,4,1,1);
    layout_->addWidget(address_,0,5,1,1);
    layout_->addWidget(web_,1,0,1,6);

    //Guardar la pagina principal
    homepage_="http://duckduckgo.com";
    address_->setText(homepage_);
    web_->load(homepage_);
    setLayout(layout_);
    setupConnections();
}

void WebBrowser::setupConnections()
{
    connect(address_,SIGNAL(returnPressed()),this,SLOT(onLoad()));
    connect(refresh_,SIGNAL(pressed()),web_,SLOT(reload()));
    connect(forward_,SIGNAL(pressed()),web_,SLOT(forward()));
    connect(back_,SIGNAL(pressed()),web_,SLOT(back()));
    connect(home_,SIGNAL(pressed()),this,SLOT(onHome()));
    connect(web_,SIGNAL(urlChanged(QUrl)),this,SLOT(onUrlChange(QUrl)));
    connect(web_,SIGNAL(loadFinished(bool)),this,SLOT(onLoadFinished(bool)));

    connect(bookmarks_,SIGNAL(pressed()),this,SLOT(onBooks()));
    connect(books,SIGNAL(url(QString)),this,SLOT(bookChange(QString)));

}

void WebBrowser::onLoad()
{
    if(!address_->text().startsWith("http://")
            && !address_->text().startsWith("https://")
            && address_->text().length()!=0)
        web_->load("http://"+address_->text());
}

void WebBrowser::onHome()
{
    web_->load(homepage_);
}

void WebBrowser::onUrlChange(QUrl url)
{
    address_->setText(url.toString());
}

void WebBrowser::onLoadFinished(bool ok)
{
    if(!ok)
        web_->load("https://duckduckgo.com/?q="+address_->text());


}

void WebBrowser::onBooks()
{
    dialog_ = new QDialog();
    QLayout* layout = new QHBoxLayout;
    books->setUrl(address_->text());
    layout->addWidget(books);
    dialog_->setLayout(layout);
    dialog_->show();
}

void WebBrowser::bookChange(QString url)
{
    dialog_->close();
    address_->setText(url);
    web_->load(url);

}

