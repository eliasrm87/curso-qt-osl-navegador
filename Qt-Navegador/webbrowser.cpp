#include "webbrowser.h"
#include <QFile>

WebBrowser::WebBrowser(QWidget *parent) :
    QWidget(parent)
{
    //crea e inicializa obejtos
    web_ = new QWebView;//crea el objeto
    address_ = new QLineEdit;//crea el objeto
    refresh_ = new QToolButton;//crea el objeto
    back_ = new QToolButton;//crea el objeto
    forward_ = new QToolButton;//crea el objeto
    home_ = new QToolButton;//crea el objeto
    addMarcador_ = new QToolButton;//crea el objeto
    layout_ = new QGridLayout;//crea el objeto
    refresh_->setIcon(QIcon(QPixmap(":/icons/resources/refresh.png")));
    back_->setIcon(QIcon(QPixmap(":/icons/resources/go-previous.png")));
    forward_->setIcon(QIcon(QPixmap(":/icons/resources/go-next.png")));
    home_->setIcon(QIcon(QPixmap(":/icons/resources/go-home.png")));
    layout_->addWidget(back_,0,0,1,1);//agregar layout y le da las cordenadas
    layout_->addWidget(forward_,0,1,1,1);//agregar layout y le da las cordenadas
    layout_->addWidget(home_,0,2,1,1);//agregar layout y le da las cordenadas
    layout_->addWidget(refresh_,0,3,1,1);//agregar layout y le da las cordenadas
    layout_->addWidget(address_,0,4,1,1);//agregar layout y le da las cordenadas
    layout_->addWidget(addMarcador_,0,5,1,1);//agregar layout y le da las cordenadas
    layout_->addWidget(web_,1,0,1,6);//agregar layout y le da las cordenadas
    homepage_="http://duckduckgo.com";//establece una paguina de inicio
    address_->setText(homepage_);//agregar la paguina a la variable direccion
    web_->load(homepage_);//cargar la paguina de inicio
    setLayout(layout_);
    setupConnections();
}

void WebBrowser::setupConnections()
{
    //crea las conecciones nesesarias
    connect(address_,SIGNAL(returnPressed()),this,SLOT(onLoad()));
    connect(refresh_,SIGNAL(pressed()),web_,SLOT(reload()));
    connect(forward_,SIGNAL(pressed()),web_,SLOT(forward()));
    connect(back_,SIGNAL(pressed()),web_,SLOT(back()));
    connect(home_,SIGNAL(pressed()),this,SLOT(onHome()));
    connect(addMarcador_,SIGNAL(pressed()),this,SLOT(emitirMarcador()));
    connect(web_,SIGNAL(urlChanged(QUrl)),this,SLOT(onUrlChange(QUrl)));
    connect(web_,SIGNAL(loadFinished(bool)),this,SLOT(onLoadFinished(bool)));

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

void WebBrowser::emitirMarcador()
{
    emit signalMarcador(address_->text());
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

void WebBrowser::goTo(QString url)
{
    address_->setText(url);
    onLoad();
}


