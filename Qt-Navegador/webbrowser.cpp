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
    layout_ = new QGridLayout;
    refresh_->setIcon(QIcon(QPixmap(":/icons/resources/refresh.png")));
    back_->setIcon(QIcon(QPixmap(":/icons/resources/go-previous.png")));
    forward_->setIcon(QIcon(QPixmap(":/icons/resources/go-next.png")));
    home_->setIcon(QIcon(QPixmap(":/icons/resources/go-home.png")));
    layout_->addWidget(back_,0,0,1,1);
    layout_->addWidget(forward_,0,1,1,1);
    layout_->addWidget(home_,0,2,1,1);
    layout_->addWidget(refresh_,0,3,1,1);
    layout_->addWidget(address_,0,4,1,1);
    layout_->addWidget(web_,1,0,1,5);

    CargarPaginaInicio();
    address_->setText(homepage_);
    web_->load(homepage_);

    setLayout(layout_);
    setupConnections();

}

void WebBrowser::CargarPaginaInicio(){
    QFile file("Inicio.txt");

    if (!file.open(QIODevice::ReadOnly)){
        homepage_="http://duckduckgo.com";
    }
    else{
        file.open(QIODevice::ReadOnly);

        QTextStream in(&file);

        QString line = in.readLine();

        homepage_= line;


    }

 file.close();
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

void WebBrowser::onLoad()
{
    if(!address_->text().startsWith("http://")
            && !address_->text().startsWith("https://")
            && address_->text().length()!=0)
        web_->load("http://"+address_->text());
    else
        web_->load(address_->text()); //Si añadimos la pagina de forma correcta
}

void WebBrowser::onHome()
{
    web_->load(homepage_);
}

void WebBrowser::onUrlChange(QUrl url)
{
    address_->setText(url.toString());
    //Añadir para guardar en fichero historial
}

void WebBrowser::onLoadFinished(bool ok)
{
    if(!ok)
        web_->load("https://duckduckgo.com/?q="+address_->text());


}
QString WebBrowser::getAddress(){
    return address_->text();
}
void WebBrowser::setAddress(QString linea){
    address_->setText(linea);
    onLoad();
}

void WebBrowser::setHomePage(){
    homepage_=address_->text();
    QFile archivo;
    archivo.setFileName("Inicio.txt");

    if (archivo.open(QFile::WriteOnly|QFile::Truncate)){

        QTextStream out(&archivo);

        QString linea = address_->text();

        out << linea << endl;
    }
        archivo.close();
}
