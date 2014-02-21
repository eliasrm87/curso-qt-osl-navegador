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
    botonmarcador_ = new QToolButton;
    botoncerrarmarcadores_ = new QToolButton;

    botonpaginanueva_= new QToolButton;

    boton_ampliar_zoom_ = new QToolButton;
    boton_reducir_zoom_ = new QToolButton;

    layout_ = new QGridLayout;


    refresh_->setIcon(QIcon(QPixmap(":/icons/resources/refresh.png")));
    back_->setIcon(QIcon(QPixmap(":/icons/resources/go-previous.png")));
    forward_->setIcon(QIcon(QPixmap(":/icons/resources/go-next.png")));
    home_->setIcon(QIcon(QPixmap(":/icons/resources/go-home.png")));

    botonmarcador_->setIcon(QIcon(QPixmap(":/icons/resources/favorito.png")));
    botoncerrarmarcadores_->setIcon(QIcon(QPixmap(":/icons/resources/cerrar_marcadores.png")));

    botonpaginanueva_->setIcon(QIcon(QPixmap(":/icons/resources/nueva_ventana.png")));

    boton_ampliar_zoom_-> setIcon(QIcon(QPixmap(":/icons/resources/ampliar_zoom.png")));
    boton_reducir_zoom_-> setIcon(QIcon(QPixmap(":/icons/resources/reducir_zoom.png")));


    // layout, parametros de la malla izq - filas, columnas,
    layout_->addWidget(back_,0,0,1,1);
    layout_->addWidget(forward_,0,1,1,1);
    layout_->addWidget(home_,0,2,1,1);
    layout_->addWidget(refresh_,0,3,1,1);
    layout_->addWidget(address_,0,4,1,1);
    layout_->addWidget(web_,1,0,1,7); //una fila y 4 columnas

    layout_->addWidget(botonmarcador_, 0,5,1,1);
    layout_->addWidget(botoncerrarmarcadores_,0,6,1,1);
    botoncerrarmarcadores_->setVisible(false);


    layout_->addWidget(botonpaginanueva_,0,7,1,1);


    //marcador_= new QMenuBar();
    //layout_->addWidget(marcador_,0,6,1,1);


    lista_marcadores_ = new QListWidget();
    layout_->addWidget(lista_marcadores_,0,8,2,2);
    lista_marcadores_->setVisible(false);


    layout_->addWidget(boton_ampliar_zoom_,0,10,1,1);
    layout_->addWidget(boton_reducir_zoom_,0,11,1,1);

    homepage_="http://duckduckgo.com";

    address_->setText(homepage_);
    web_->load(homepage_);
    setLayout(layout_);
    setupConnections();
    show();


    //ventanita_ = new QWebView();
    //ventanita_->page()->setLinkDelegationPolicy(QWebPage::DelegateAllLinks);
    //ventanita_->setUrl(QString("www.google.es"));


}

void WebBrowser::setupConnections()
{
    //conexiones para que todo funcione
    connect(address_,SIGNAL(returnPressed()),this,SLOT(onLoad()));
    connect(refresh_,SIGNAL(pressed()),web_,SLOT(reload()));
    connect(forward_,SIGNAL(pressed()),web_,SLOT(forward()));
    connect(back_,SIGNAL(pressed()),web_,SLOT(back()));
    connect(home_,SIGNAL(pressed()),this,SLOT(onHome()));
    connect(web_,SIGNAL(urlChanged(QUrl)),this,SLOT(onUrlChange(QUrl)));
    connect(web_,SIGNAL(loadFinished(bool)),this,SLOT(onLoadFinished(bool)));

    //
    connect(botonmarcador_,SIGNAL(pressed()),this,SLOT(marcadores()));
    connect(botonpaginanueva_, SIGNAL(pressed()), this, SLOT(nueva_ventana()));


    //conecto los dos botones del zoom
    connect(boton_ampliar_zoom_, SIGNAL(pressed()), this, SLOT(ampliar_zoom()));
    connect(boton_reducir_zoom_, SIGNAL(pressed()), this, SLOT(reducir_zoom()));
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

void WebBrowser::onLoadFinished(bool ok)
{
    if(!ok)
        web_->load("https://duckduckgo.com/?q="+address_->text());

}

void WebBrowser::marcadores()
{

    lista_marcadores_->clear();
    lista_marcadores_->setVisible(true);
    botoncerrarmarcadores_->setVisible(true);

    QFile Archivo("marcadores.txt");
    Archivo.open(QIODevice::ReadOnly | QIODevice::Text);

        QTextStream in(&Archivo);
        //int i=0;
        while (!in.atEnd()) {
            QString Line = in.readLine();

            //añado a mi barra de dirección los string de la lista
            //direc_ = new QAction(Line,this);
            //marcador_->addAction(direc_);
            //connect(direc_, SIGNAL(triggered()), this, SLOT(cargarpagina()));


            lista_marcadores_->addItem(new QListWidgetItem(Line));

            //item_lista_=new QListWidgetItem(Line,lista_marcadores_);
           // item_lista_->setText(Line);
           // lista_marcadores_->insertItem(i, item_lista_);
          //  i++;
            connect(lista_marcadores_, SIGNAL(itemClicked(QListWidgetItem *)),this,SLOT(cargarpagina(QListWidgetItem *)));

            connect(botoncerrarmarcadores_, SIGNAL(pressed()) ,this ,SLOT(cerrar_marcadores()));

        }

    Archivo.close();
    }

void WebBrowser::cerrar_marcadores(){

    lista_marcadores_->setVisible(false);
    botoncerrarmarcadores_->setVisible(false);
}



void WebBrowser::cargarpagina(QListWidgetItem *item){


   // qDebug()<< item->text();
   // address_->setText(((QAction*)QObject::sender())->text());

   address_->setText(item->text());
    onLoad();

}

void WebBrowser::nueva_ventana() {

    //meto webview
    brow_ = new QWebView();
    brow_->load(QUrl ("http://google.com"));
    brow_->show();

    //meto la ventanita en el layout
    caja_ = new QVBoxLayout();
    caja_->insertWidget(0,brow_,0,Qt::AlignBottom);

    //meto la ventanita en el tab
    tab_ = new QTabWidget();
    tab_->setLayout(caja_);
    tab_->addTab(new QWidget,"Nueva Ventana");
    //tab_->resize(1,1);

    tabi_= tab_->tabBar();
    cerrar_ = new QPushButton();

    cerrar_->setText("X");
    cerrar_->setStyleSheet("border:none");
    tabi_->setTabButton(tabi_->count() -1, QTabBar::RightSide,cerrar_);

    layout_->addWidget(tab_,1,0,1,1);


    connect(cerrar_,SIGNAL(clicked()), this, SLOT(cerrar_nueva_ventana()));

}


void WebBrowser::cerrar_nueva_ventana(){

   // tab_->setVisible(false);

    tab_->close();

}


void WebBrowser::ampliar_zoom(){
    //colócame el zoom del navegador al valor actual que tiene ahora mismo sumándole una cantidad
     web_->setZoomFactor(web_->zoomFactor()+ 0.25);

     //si mi cutrísima etiqueta está abierta
     if (brow_)
        brow_->setZoomFactor(brow_->zoomFactor()+ 0.25);
}

void WebBrowser::reducir_zoom(){
     web_->setZoomFactor(web_->zoomFactor()- 0.25);

     if (brow_)
         brow_->setZoomFactor(brow_->zoomFactor()- 0.25);
}


