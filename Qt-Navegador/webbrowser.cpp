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
    z1_=new QToolButton;
    z1_->setIcon(QIcon(QPixmap(":/icons/Zoom-In-icon.png")));
    z2_=new QToolButton;
    z2_->setIcon(QIcon(QPixmap(":/icons/Zoom-Out-icon.png")));

    venta_ = new QToolButton;
    venta_->setIcon(QIcon(QPixmap(":/icons/blue-plus-icon.png")));

    layout_->addWidget(back_,0,0,1,1);
    layout_->addWidget(forward_,0,1,1,1);
    layout_->addWidget(home_,0,2,1,1);
    layout_->addWidget(refresh_,0,3,1,1);
    layout_->addWidget(address_,0,4,1,1);
    layout_->addWidget(web_,1,0,1,5);
    layout_->addWidget(z1_,0,10,1,1);
    layout_->addWidget(z2_,0,11,1,1);

    marcador_ = new QToolButton;
    marcador_->setIcon(QIcon(QPixmap(":/icons/Start-Menu-Favorites-icon.png")));
    layout_->addWidget(marcador_,0,5,1,1);

    lista_= new QListWidget();
    layout_->addWidget(lista_,0,6,2,2);
    lista_->setVisible(false);
    layout_->addWidget(venta_,0,12,1,1);
    control_ = false;

    homepage_="http://duckduckgo.com";
    address_->setText(homepage_);
    web_->load(homepage_);
    setLayout(layout_);
    setupConnections();
    show();
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
    connect(marcador_,SIGNAL(pressed()),this,SLOT(marcadores()));
    connect(z1_,SIGNAL(pressed()),this,SLOT(zoom1()));
    connect(z2_,SIGNAL(pressed()),this,SLOT(zoom2()));
    connect(venta_, SIGNAL(pressed()),this,SLOT(new_win()));
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

void WebBrowser::onHome(){
     web_->load(homepage_);
}

void WebBrowser::onUrlChange(QUrl url){
    address_->setText(url.toString());
}

void WebBrowser::onLoadFinished(bool ok){
    if(!ok)
        web_->load("https://duckduckgo.com/?q="+address_->text());
}

void WebBrowser::marcadores()
{
    if (!control_)
    {
    QFile file("marcadores.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        control_=true;
        QTextStream in(&file);
        in.setCodec("UTF-8"); // change the file codec to UTF-8.
        int i=0;
        lista_->setVisible(true);
        while(!in.atEnd())
        {

            QString line = in.readLine();

            //cout<<"leo= "<<endl;
//            direccion_= new QAction (line,this);
//            fav_->addAction(direccion_);
//            connect(direccion_,SIGNAL(triggered()),this, SLOT(ir_a()))
            lista_->addItem(new QListWidgetItem(line));
            item_ = new QListWidgetItem(line, lista_);
            item_->setText(line);
            lista_->insertItem(i,item_);
            i++;
            //connect(direccion_,SIGNAL(triggered()),this, SLOT(ir_a()));

            connect(lista_,SIGNAL(itemDoubleClicked(QListWidgetItem *)),this, SLOT(ir_a(QListWidgetItem *)));
        }
        file.close();
    }
    }
}


void WebBrowser::ir_a(QListWidgetItem *it){
//    address_->setText(((QAction*)QObject::sender())->text());
    address_->setText(it->text());
    onLoad();
}

void WebBrowser::zoom1(){
    web_->setZoomFactor(web_->zoomFactor()+0.25);
}

void WebBrowser::zoom2(){
    web_->setZoomFactor(web_->zoomFactor()-0.25);
}

void WebBrowser::new_win()
{
    base_=new QWebView();
    base_->load(QUrl ("http://www.youtube.com/"));
    base_->show();
    caja_=new QVBoxLayout();
    caja_->insertWidget(0,base_,0,Qt::AlignBottom);
    ventana_=new QTabWidget();
    ventana_->setLayout(caja_);
    ventana_->addTab(new QWidget,"New");
    tab_= ventana_->tabBar();
    salir_=new QPushButton();
    salir_->setText("x");
    tab_->setTabButton(tab_->count()-1,QTabBar::RightSide,salir_);
    layout_->addWidget(ventana_,1,0,1,1);
    connect(salir_,SIGNAL(pressed()),this,SLOT(cerrar2()));
}

void WebBrowser::cerrar2(){
    ventana_->close();
}
