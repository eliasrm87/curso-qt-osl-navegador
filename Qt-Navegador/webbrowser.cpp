#include "webbrowser.h"

WebBrowser::WebBrowser(QWidget *parent): QWidget(parent) {
    web_ = new QWebView(this);
    address_ = new QLineEdit(this);
    refresh_ = new QToolButton(this);
    back_ = new QToolButton(this);
    forward_ = new QToolButton(this);
    home_ = new QToolButton(this);
    layout_ = new QGridLayout(this);

    refresh_->setIcon(QIcon(QPixmap(":/icons/resources/refresh.png")));
    back_->setIcon(QIcon(QPixmap(":/icons/resources/go-previous.png")));
    forward_->setIcon(QIcon(QPixmap(":/icons/resources/go-next.png")));
    home_->setIcon(QIcon(QPixmap(":/icons/resources/go-home.png")));

    layout_->addWidget(back_,    0, 0, 1, 1);
    layout_->addWidget(forward_, 0, 1, 1, 1);
    layout_->addWidget(home_,    0, 2, 1, 1);
    layout_->addWidget(refresh_, 0, 3, 1, 1);
    layout_->addWidget(address_, 0, 4, 1, 1);
    layout_->addWidget(web_,     1, 0, 1, 5);

    homepage_="http://duckduckgo.com";
    address_->setText(homepage_);
    web_->load(homepage_);
    setLayout(layout_);
    setupConnections();
}

void WebBrowser::setupConnections() {
    connect(address_, SIGNAL(returnPressed()),    this, SLOT(onLoad()));
    connect(refresh_, SIGNAL(pressed()),          web_, SLOT(reload()));
    connect(forward_, SIGNAL(pressed()),          web_, SLOT(forward()));
    connect(back_,    SIGNAL(pressed()),          web_, SLOT(back()));
    connect(home_,    SIGNAL(pressed()),          this, SLOT(onHome()));
    connect(web_,     SIGNAL(urlChanged(QUrl)),   this, SLOT(onUrlChange(QUrl)));
    connect(web_,     SIGNAL(loadFinished(bool)), this, SLOT(onLoadFinished(bool)));
}

void WebBrowser::onLoad() {
    if(!address_->text().startsWith("http://") &&
       !address_->text().startsWith("https://") &&
       !address_->text().isEmpty())
        web_->load("http://"+address_->text());
    else if (!address_->text().isEmpty())
      web_->load(address_->text());
}

void WebBrowser::onHome() {
    web_->load(homepage_);
}

void WebBrowser::onUrlChange(QUrl url) {
    address_->setText(url.toString());
}

void WebBrowser::onLoadFinished(bool ok) {
    if(!ok)
        web_->load("https://duckduckgo.com/?q="+address_->text());
}

