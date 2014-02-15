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
    anadirMarcador_ = new  QToolButton;
    layout_ = new QGridLayout;
    refresh_->setIcon(QIcon(QPixmap(":/icons/resources/refresh.png")));
    back_->setIcon(QIcon(QPixmap(":/icons/resources/go-previous.png")));
    forward_->setIcon(QIcon(QPixmap(":/icons/resources/go-next.png")));
    home_->setIcon(QIcon(QPixmap(":/icons/resources/go-home.png")));

    //El layout permite colocar cada control donde queramos y se redimensionarán
    // cuando se cambie el tamaño de la ventana.

    //Se establece cada widget en una posición del layout.
    //Los dos primeros parámetros indican la posición en la que se inserta el widget.
    //Los dos últimos parámetros indican cuantas filas y columnas ocupa cada widget.
    layout_->addWidget(back_,0,0,1,1);
    layout_->addWidget(forward_,0,1,1,1);
    layout_->addWidget(home_,0,2,1,1);
    layout_->addWidget(refresh_,0,3,1,1);
    layout_->addWidget(address_,0,4,1,1);
    layout_->addWidget(anadirMarcador_,0,5,1,1);
    layout_->addWidget(web_,1,0,1,6);

    homepage_="http://duckduckgo.com";
    address_->setText(homepage_);
    web_->load(homepage_);
    //Se establece el layout que hemos configurado como layout de nuestro navegador.
    this->setLayout(layout_);
    this->setupConnections();

}

void WebBrowser::setupConnections()
{
    //Cuando se pulsa enter en la caja de texto de la dirección se invoca al
    // slot (método) "onLoad()" que carga la página que se ha escrito.
    connect(address_,SIGNAL(returnPressed()),this,SLOT(onLoad()));
    connect(refresh_,SIGNAL(pressed()),web_,SLOT(reload()));
    connect(forward_,SIGNAL(pressed()),web_,SLOT(forward()));
    connect(back_,SIGNAL(pressed()),web_,SLOT(back()));
    connect(home_,SIGNAL(pressed()),this,SLOT(onHome()));
    connect(web_,SIGNAL(urlChanged(QUrl)),this,SLOT(onUrlChange(QUrl)));
    connect(web_,SIGNAL(loadFinished(bool)),this,SLOT(onLoadFinished(bool)));

    //Cuando se pulse sobre el botón de añadir marcador se ejecutará el
    // slot "onAnadirMarcador".
    connect(anadirMarcador_,SIGNAL(pressed()),this,SLOT(onAnadirMarcador()));
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

void WebBrowser::onAnadirMarcador()
{
    //Se emite la señal que envía la dirección URL actual.
    //"mainWindow" capturará esta señal y añadirá la dirección a los marcadores.
    emit signalAnadirMarcador(address_->text());
}

void WebBrowser::goTo(QString URL)
{
    //
    address_->setText(URL);
    onLoad();
}


