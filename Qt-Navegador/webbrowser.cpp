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
    //Por mi------
    marcadores_ = new QToolButton;
    //--------
    layout_ = new QGridLayout;
    refresh_->setIcon(QIcon(QPixmap(":/icons/resources/refresh.png")));
    back_->setIcon(QIcon(QPixmap(":/icons/resources/go-previous.png")));
    forward_->setIcon(QIcon(QPixmap(":/icons/resources/go-next.png")));
    home_->setIcon(QIcon(QPixmap(":/icons/resources/go-home.png")));
    //Por mi--------
    marcadores_->setIcon(QIcon(QPixmap(":/icons/resources/marcador.png")));
    //---------
    layout_->addWidget(back_,0,0,1,1); //Los dos primeros numeros son los que dictan donde van
    layout_->addWidget(forward_,0,1,1,1); //Los dos segundos numeros es lo qeu avanza cada uno
    layout_->addWidget(home_,0,2,1,1);
    layout_->addWidget(refresh_,0,3,1,1);
    layout_->addWidget(address_,0,4,1,1);
    layout_->addWidget(web_,2,0,1,6);
    //Por mi-------
    layout_->addWidget(marcadores_,0,5,1,1);
    //------
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
    //Por mi
    connect(marcadores_,SIGNAL(pressed()),this,SLOT(onMarcador()));
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

//Por mi

void WebBrowser::onLoad2(void){
    web_->load(((QAction*)QObject::sender())->data().toString());
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


//Por mi

void WebBrowser::onMarcador(){
    listaMarcadores_.push_back(address_->text());


    listaNameMarcadores_.push_back("a");
    emit(sMarcador());

}

int WebBrowser::get_tamMarcadores(){
    return listaMarcadores_.size();
}

QString WebBrowser::get_marcador(int i){
    return listaMarcadores_.at(i);
}

QString WebBrowser::get_nameMarcador(int i)
{
    return listaNameMarcadores_.at(i);
}
