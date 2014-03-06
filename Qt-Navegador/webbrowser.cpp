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
    layout_->addWidget(web_,1,0,1,7);
    homepage_="http://duckduckgo.com";
    address_->setText(homepage_);
    web_->load(homepage_);

    // Zoom
    moreZoom_ = new QToolButton;
    lessZoom_ = new QToolButton;
    moreZoom_->setIcon(QIcon(":/icons/resources/Zoom_mas.png"));
    lessZoom_->setIcon(QIcon(":/icons/resources/Zoom_menos.png"));
    layout_->addWidget(moreZoom_,0,5,1,1);
    layout_->addWidget(lessZoom_,0,6,1,1);

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
    connect(moreZoom_,SIGNAL(pressed()), this, SLOT(aumentarZoom()));
    connect(lessZoom_,SIGNAL(pressed()),this,SLOT(disminuirZoom()));
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

    //Añadimos la url al historial
    agregarHistorial(url.toString());
}

void WebBrowser::onLoadFinished(bool ok)
{
    if(!ok)
        web_->load("https://duckduckgo.com/?q="+address_->text());


}

void WebBrowser::aumentarZoom()
{
    web_->setZoomFactor(web_->zoomFactor() + 0.1);
}

void WebBrowser::disminuirZoom()
{
    web_->setZoomFactor(web_->zoomFactor() - 0.1);
}

QString WebBrowser::getAddress()
{
    return address_->text();
}

void WebBrowser::setAddress(QString address)
{
    address_->setText(address);
    onLoad();
}

QString WebBrowser::getHomepage()
{
    return homepage_;
}

void WebBrowser::setHomepage(QString homepage)
{
    homepage_ = homepage;
}

void WebBrowser::agregarHistorial(QString address)
{
    QFile historial("../historial.txt");
    historial.open(QIODevice::Append);

    QTextStream out(&historial);
    out << address << endl;

    historial.close();
}

QWebView *WebBrowser::getWeb()
{
    return web_;
}
