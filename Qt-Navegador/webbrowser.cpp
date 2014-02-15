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

    homedefault_ = new QToolButton;
    homedefault_ -> setIcon(QIcon(QPixmap(":/icons/resources/insert-link.png")));

    layout_->addWidget(back_,1,0,1,1);
    layout_->addWidget(forward_,1,1,1,1);
    layout_->addWidget(home_,1,2,1,1);
    layout_->addWidget(refresh_,1,3,1,1);
    layout_->addWidget(address_,1,4,1,1);
    layout_->addWidget(web_,2,0,1,5);

    layout_ ->addWidget(homedefault_,0,5,1,1);

    homepage_="http://duckduckgo.com";
    address_->setText(homepage_);
    web_->load(homepage_);
    setLayout(layout_);
    setupConnections();

    menu_ = new QMenuBar (this);
    mnuEditar_ = new QMenu(tr("&Editar"),this);
    menu_ -> addMenu (mnuEditar_);


    actEditarH_ = new QAction (tr("&Historial"), this);
    actEditarH_ -> setShortcut(QKeySequence(Qt::CTRL + Qt::Key_H)); //Opcional
    mnuEditar_ -> addAction (actEditarH_);

    actEditarM_ = new QAction (tr("&Marcadores"), this);
    actEditarM_ -> setShortcut(QKeySequence(Qt::CTRL + Qt::Key_B)); //Opcional
    mnuEditar_ -> addAction (actEditarM_);
    connect(actEditarH_, SIGNAL (triggered()), this, SLOT(alHistorial()));

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

    connect(homedefault_, SIGNAL(pressed()), this, SLOT(onHomedefault(QUrl)));
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

void WebBrowser::onHomedefault(QUrl url) {


   homepage_ = url.toString();

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

void WebBrowser::alHistorial(){
     /*QMessageBox mensaje;
     mensaje.setText("Mensaje de prueba");
     mensaje.exec();*/

    //QWebHistory
}


