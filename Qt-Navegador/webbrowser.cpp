#include "webbrowser.h"
#include "markerswindow.h"

#include <QWidgetAction>
#include <QSettings>

WebBrowser::WebBrowser(QWidget *parent): QWidget(parent) {
    web_ = new QWebView(this);
    toolbar_ = new QToolBar(this);
    address_ = new QLineEdit(this);
    refresh_ = new QAction(tr("Actualizar"), this);
    back_ = new QAction(tr("Anterior"), this);
    forward_ = new QAction(tr("Siguiente"), this);
    home_ = new QAction(tr("Inicio"), this);
    markers_ = new QAction(tr("Marcadores"), this);
    config_ = new QAction(tr("Configuración"), this);
    history_ = new QAction(tr("Historial"), this);
    layout_ = new QGridLayout(this);

    QWidgetAction* lineAction = new QWidgetAction(this);
    lineAction->setDefaultWidget(address_);

    refresh_->setIcon(QIcon(QPixmap(":/icons/resources/refresh.png")));
    back_->setIcon(QIcon(QPixmap(":/icons/resources/go-previous.png")));
    forward_->setIcon(QIcon(QPixmap(":/icons/resources/go-next.png")));
    home_->setIcon(QIcon(QPixmap(":/icons/resources/go-home.png")));
    markers_->setIcon(QIcon(QPixmap(":/icons/resources/markers.png")));
    config_->setIcon(QIcon(QPixmap(":/icons/resources/config.png")));
    history_->setIcon(QIcon(QPixmap(":/icons/resources/history.png")));

    toolbar_->addAction(back_);
    toolbar_->addAction(forward_);
    toolbar_->addAction(home_);
    toolbar_->addAction(refresh_);
    toolbar_->addAction(lineAction);
    toolbar_->addAction(markers_);
    toolbar_->addAction(config_);
    toolbar_->addAction(history_);

    layout_->addWidget(toolbar_, 0, 0);
    layout_->addWidget(web_,     1, 0);

    homepage_="http://duckduckgo.com";
    address_->setText(homepage_);
    web_->load(homepage_);
    setLayout(layout_);

    setupConnections();
    loadMarkers();
}

WebBrowser::~WebBrowser() {
  saveMarkers();
}

void WebBrowser::setupConnections() {
    connect(address_, SIGNAL(returnPressed()),    this, SLOT(onLoad()));
    connect(refresh_, SIGNAL(triggered()),        web_, SLOT(reload()));
    connect(forward_, SIGNAL(triggered()),        web_, SLOT(forward()));
    connect(back_,    SIGNAL(triggered()),        web_, SLOT(back()));
    connect(home_,    SIGNAL(triggered()),        this, SLOT(onHome()));
    connect(markers_, SIGNAL(triggered()),        this, SLOT(onMarkers()));
    connect(web_,     SIGNAL(urlChanged(QUrl)),   this, SLOT(onUrlChange(QUrl)));
    connect(web_,     SIGNAL(loadFinished(bool)), this, SLOT(onLoadFinished(bool)));
}

void WebBrowser::onLoad() {
    if(!address_->text().startsWith("http://") &&
       !address_->text().startsWith("https://") &&
       !address_->text().isEmpty())
        web_->load("http://" + address_->text());
    else if (!address_->text().isEmpty())
      web_->load(address_->text());
}

void WebBrowser::onHome() {
    web_->load(homepage_);
}

void WebBrowser::onMarkers() {
    MarkersWindow wnd;
    wnd.setMarkers(markerList_);
    wnd.setCurrentURL(address_->text());

    connect(&wnd, SIGNAL(markerLaunched(QString)), this, SLOT(onLoadURL(QString)));
    connect(&wnd, SIGNAL(markersSaved(QList<QString>)), this, SLOT(setMarkers(QList<QString>)));

    wnd.setModal(true);
    wnd.setVisible(true);
    wnd.exec();
}

void WebBrowser::onLoadURL(QString url) {
    address_->setText(url);
    onLoad();
}

void WebBrowser::onUrlChange(QUrl url) {
    address_->setText(url.toString());
}

void WebBrowser::onLoadFinished(bool ok) {
    if(!ok)
        web_->load("https://duckduckgo.com/?q=" + address_->text());
}

void WebBrowser::setMarkers(QList<QString> markers) {
    markerList_ = markers;
}

void WebBrowser::loadMarkers() {
    markerList_.clear();
    QSettings settings("markers.ini", QSettings::IniFormat);

    settings.beginGroup("MarkersData");
    int size = settings.beginReadArray("markers");
    for (int i = 0; i < size; ++i) {
        settings.setArrayIndex(i);
        markerList_.append(settings.value("marker").toString());
    }
    settings.endArray();
    settings.endGroup();
}

void WebBrowser::saveMarkers() {
    QSettings settings("markers.ini", QSettings::IniFormat);

    settings.beginGroup("MarkersData");
    settings.beginWriteArray("markers");
    for (int i = 0; i < markerList_.size(); ++i) {
        settings.setArrayIndex(i);
        settings.setValue("marker", markerList_.at(i));
    }
    settings.endArray();
    settings.endGroup();
}
