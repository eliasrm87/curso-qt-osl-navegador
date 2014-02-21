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


    zoomMas_ = new QToolButton;
    zoomMenos_ = new QToolButton;
    zoomOriginal_ = new QToolButton;
    zoomMas_->setIcon(QIcon(QPixmap(":/icons/resources/zoom-in.png")));
    zoomMenos_->setIcon(QIcon(QPixmap(":/icons/resources/zoom-out.png")));
    zoomOriginal_->setIcon(QIcon(QPixmap(":/icons/resources/zoom-original.png")));

    zoomMas_ -> setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Plus));
    zoomMenos_ -> setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Minus));
    zoomOriginal_ -> setShortcut(QKeySequence(Qt::CTRL + Qt::Key_0));


    layout_->addWidget(back_,0,0,1,1);
    layout_->addWidget(forward_,0,1,1,1);
    layout_->addWidget(home_,0,2,1,1);
    layout_->addWidget(refresh_,0,3,1,1);
    layout_->addWidget(address_,0,4,1,1);

    layout_->addWidget(zoomMenos_,0,5,1,1);
    layout_->addWidget(zoomOriginal_,0,6,1,1);
    layout_->addWidget(zoomMas_,0,7,1,1);

    layout_->addWidget(web_,1,0,1,8);
    QFile fileHome("homepage.txt");
    fileHome.open(QIODevice::ReadOnly);
    QTextStream in(&fileHome);
    homepage_ = in.readLine();
    fileHome.close();
    //homepage_="http://duckduckgo.com";
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
    connect(zoomMas_,SIGNAL(pressed()), this, SLOT(ampliar()));
    connect(zoomMenos_,SIGNAL(pressed()), this, SLOT(reducir()));
    connect(zoomOriginal_,SIGNAL(pressed()), this, SLOT(original()));

}

void WebBrowser::ampliar () {
    web_->setZoomFactor( web_->zoomFactor() + 0.2);
}

void WebBrowser::reducir () {
    web_->setZoomFactor( web_->zoomFactor() - 0.2);
}

void WebBrowser::original () {
    web_->setZoomFactor(1);
}


void WebBrowser::onLoad()
{
    if(!address_->text().startsWith("http://")
            && !address_->text().startsWith("https://")
            && address_->text().length()!=0) {
        web_->load("http://"+address_->text());
    }
    else {
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
}

void WebBrowser::onLoadFinished(bool ok)
{
    if(!ok) {
        web_->load("https://duckduckgo.com/?q="+address_->text());
    }
    setHistorial();
}

QLineEdit* WebBrowser::getAddress() {
    return address_;
}

void WebBrowser::setAddress(QString linea) {
    QUrl url(linea);
    web_->load(url);
}


void WebBrowser::setHomePage () {
    homepage_ = address_->text();
    QFile fileHome("homepage.txt");
    fileHome.open(QIODevice::WriteOnly);
    QTextStream out(&fileHome);
    out << homepage_ << endl;
    fileHome.close();
}


void WebBrowser::setHistorial () {
    QFile fileHistorial("historial.txt");
    fileHistorial.open(QIODevice::Append);
    QTextStream out(&fileHistorial);
    out << address_->text() << endl;
    fileHistorial.close();
}

