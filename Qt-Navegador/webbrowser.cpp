#include "webbrowser.h"

WebBrowser::WebBrowser(QWidget *parent) :
    QWidget(parent)
{
    /*Inicializando Variables A Usar*/
    web_ = new QWebView(this); //poner el padre sirve sobretodo para el recolector de basura
    address_ = new QLineEdit(this); //Cuando el objeto padre se muera, QT matara a sus hijos.
    refresh_ = new QToolButton;
    back_ = new QToolButton;
    forward_ = new QToolButton;
    home_ = new QToolButton;
    layout_ = new QGridLayout;

    Icon();
    DrawIcon();

    setLayout(layout_);

    setupConnections();
}

void WebBrowser::load()
{
    qDebug()<<"Pagina por defecto:"<<homepage_;
    address_->setText(homepage_);
    web_->load(homepage_);
}


QString WebBrowser::get_homepage()
{
    return homepage_;
}

void WebBrowser::set_homepage(QString homepage)
{
    homepage_ = homepage;
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
}

QString WebBrowser::getAddress()
{
    return address_->text();
}

void WebBrowser::setAddress(QString address)
{
    address_->setText(address);
    //onLoad();
}

void WebBrowser::onLoad()
{
    if(!address_->text().startsWith("http://")
            && !address_->text().startsWith("https://")
            && address_->text().length()!=0)
        web_->load("http://"+address_->text());
    else
        web_->load(address_->text());
}

void WebBrowser::onHome()
{
    web_->load(homepage_);
}

void WebBrowser::onUrlChange(QUrl url)
{
    address_->setText(url.toString());
}

void WebBrowser::onLoadFinished(bool ok) //primero buscamos la web sino existe buscamos en el buscador
{
    if(!ok)
        web_->load("https://duckduckgo.com/?q="+address_->text());
}

void WebBrowser::AcercarZoom()
{
//    ((QAction*)QObject::sender()).text
    web_->setZoomFactor(web_->zoomFactor() + 0.1);
}

void WebBrowser::AlejarZoom()
{
    web_->setZoomFactor(web_->zoomFactor() - 0.1);
}

void WebBrowser::Icon(){
    refresh_->setIcon(QIcon(QPixmap(":/icons/resources/refresh.png")));
    back_->setIcon(QIcon(QPixmap(":/icons/resources/go-previous.png")));
    forward_->setIcon(QIcon(QPixmap(":/icons/resources/go-next.png")));
    home_->setIcon(QIcon(QPixmap(":/icons/resources/go-home.png")));
}

void WebBrowser::DrawIcon()
{
    layout_->addWidget(back_,0,0,1,1);
    layout_->addWidget(forward_,0,1,1,1);
    layout_->addWidget(home_,0,2,1,1);
    layout_->addWidget(refresh_,0,3,1,1);
    layout_->addWidget(address_,0,4,1,1);
    layout_->addWidget(web_,1,0,1,5);

}

QWebView *WebBrowser::getWeb()
{
    return web_;
}
