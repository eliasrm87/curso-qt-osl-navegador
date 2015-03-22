/*
 *  Adrián Rodríguez Bazaga
 *  alu0100826456@ull.edu.es
 *  Navegador web - Curso de QT
 *
 * */

#include "webbrowser.h"

WebBrowser::WebBrowser(QWidget *parent) :
    QWidget(parent)
{
    web_ = new QWebView(this);
    address_ = new QLineEdit(this);
    refresh_ = new QToolButton;
    back_ = new QToolButton;
    forward_ = new QToolButton;
    home_ = new QToolButton;
    Ampliar_ = new QToolButton;
    Reducir_ = new QToolButton;
    Original_ = new QToolButton;
    ventanaAdd_ = new QToolButton;
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
    //layout_->addWidget(web_,1,0,1,0);

    //Zoom
    Ampliar_->setIcon(QIcon(QPixmap(":/icons/resources/zoom-in.png")));
    Reducir_->setIcon(QIcon(QPixmap(":/icons/resources/zoom-out.png")));
    Original_->setIcon(QIcon(QPixmap(":/icons/resources/zoom-original.png")));
    ventanaAdd_->setIcon(QIcon(QPixmap(":/icons/resources/new_tab.png")));
    layout_->addWidget(ventanaAdd_,1,6,1,1);
    layout_->addWidget(Ampliar_,0,5,1,1);
    layout_->addWidget(Reducir_,0,6,1,1);
    layout_->addWidget(Original_,0,7,1,1);
    //

    //Implementación homepage
    QFile fileHome("homepage.txt");
    fileHome.open(QIODevice::ReadOnly);
    QTextStream in(&fileHome);
    homepage_ = in.readLine();
    fileHome.close();
    //
    address_->setText(homepage_);
    web_->load(homepage_);

    //Pestañas
    tab_ = new QTabWidget();
    tab_->addTab(web_,homepage_);
    tab_->setTabsClosable(true);
    layout_->addWidget(tab_,2,0,1,9);
    //

    //Menu contextual
    contextMenu = new QMenu;
    setContextMenuPolicy(Qt::CustomContextMenu);

    actCM1 = contextMenu->addAction("Ampliar zoom");
    actCM2 = contextMenu->addAction("Reducir zoom");
    actCM3 = contextMenu->addAction("Zoom por defecto");

    connect(this, SIGNAL(customContextMenuRequested(const QPoint)), this, SLOT(contextMenuRequested(QPoint)));
    connect(actCM1,SIGNAL(triggered()),this,SLOT(onAmpliar()));
    connect(actCM2,SIGNAL(triggered()),this,SLOT(onReducir()));
    connect(actCM3,SIGNAL(triggered()),this,SLOT(onOriginal()));
    //

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
    //Zoom
    connect(Ampliar_,SIGNAL(pressed()), this, SLOT(onAmpliar()));
    connect(Reducir_,SIGNAL(pressed()), this, SLOT(onReducir()));
    connect(Original_,SIGNAL(pressed()), this, SLOT(onOriginal()));
    //
    //Pestañas
    connect(ventanaAdd_,SIGNAL(pressed()), this, SLOT(onNuevaVentana()));
    connect(tab_,SIGNAL(tabCloseRequested(int)), this, SLOT(onCerrarVentana(int)));
    connect(tab_,SIGNAL(currentChanged(int)), this, SLOT(onTabCambia(int)));
    //
}

void WebBrowser::onLoad()
{
    if(!address_->text().startsWith("http://")
            && !address_->text().startsWith("https://")
            && address_->text().length()!=0) {
        tab_->setTabText(tab_->currentIndex(), address_->text());
        QWebView* vista = (QWebView*)tab_->widget(tab_->currentIndex());
        vista->load("http://"+address_->text());
    }
    else {
        tab_->setTabText(tab_->currentIndex(), address_->text());
        QWebView* vista = (QWebView*)tab_->widget(tab_->currentIndex());
        vista->load("http://"+address_->text());
    }
}

void WebBrowser::onHome()
{
    tab_->setTabText(tab_->currentIndex(), homepage_);
    QWebView* vista = (QWebView*)tab_->widget(tab_->currentIndex());
    vista->load(homepage_);
}

void WebBrowser::onUrlChange(QUrl url)
{
    address_->setText(url.toString());
    tab_->setTabText(tab_->currentIndex(), url.toString());
    //Añadimos la página que se ha cargado al historial
    QFile file("historial.txt");
    if (!file.open(QIODevice::Append | QIODevice::Text))
    return;

    QTextStream out(&file);
    out << address_->text() << "\n";
    file.close();

    emit signalRB(); //Emitimos señal que capta el MainWindow para actualizar el menú de ver historial
}

void WebBrowser::onLoadFinished(bool ok)
{
    if(!ok) {
        web_->load("https://www.google.es/search?q="+address_->text());
    }
}

//Imp. clase
QLineEdit* WebBrowser::getAddress() {
    return address_;
}

void WebBrowser::setAddress(QString linea) {
    QUrl url(linea);
    tab_->setTabText(tab_->currentIndex(), linea);
    QWebView* vista = (QWebView*)tab_->widget(tab_->currentIndex());
    vista->load(url);
}

void WebBrowser::setHomePage () {
    homepage_ = address_->text();
    QFile fileHome("homepage.txt");
    fileHome.open(QIODevice::WriteOnly);
    QTextStream out(&fileHome);
    out << homepage_ << endl;
    fileHome.close();
}
//


//Zoom
void WebBrowser::onAmpliar () {
    web_->setZoomFactor( web_->zoomFactor() + 0.2);
}

void WebBrowser::onReducir () {
    web_->setZoomFactor( web_->zoomFactor() - 0.2);
}

void WebBrowser::onOriginal () {
    web_->setZoomFactor(1);
}
//

//Pestañas
void WebBrowser::onNuevaVentana() {
    tab_->addTab(new QWebView,"Nueva ventana");
    tab_->resize(1,1);
    tab_->setTabText(tab_->count()-1, homepage_);
    QWebView* vista = (QWebView*)tab_->widget(tab_->count()-1);
    vista->load(homepage_);
}

void WebBrowser::onCerrarVentana(int index){
    if(tab_->count()!=1)
    {
        tab_->removeTab(index);
    }
}

void WebBrowser::onTabCambia(int index){
    if(index!=-1)
    {
        address_->setText(tab_->tabText(index));
    }
    else
    {
        address_->clear();
    }
}
//

//Menu contextual
void WebBrowser::contextMenuRequested(QPoint point)
{
    contextMenu->popup(mapToGlobal(point));
};
//


