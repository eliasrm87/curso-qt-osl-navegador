#include "webbrowser.h"
#include <QDebug>

WebBrowser::WebBrowser(QWidget *parent) :
    QWidget(parent)
{



    web_ = new QWebView(this);
    address_ = new QLineEdit(this);
    refresh_ = new QToolButton(this);
    back_ = new QToolButton(this);
    forward_ = new QToolButton(this);
    home_ = new QToolButton(this);
    bookmarks_ = new QToolButton(this);
    layout_ = new QGridLayout(this);



    refresh_->setIcon(QIcon(QPixmap(":/icons/resources/refresh.png")));
    back_->setIcon(QIcon(QPixmap(":/icons/resources/go-previous.png")));
    forward_->setIcon(QIcon(QPixmap(":/icons/resources/go-next.png")));
    home_->setIcon(QIcon(QPixmap(":/icons/resources/go-home.png")));
    bookmarks_->setIcon(QIcon(QPixmap(":/icons/resources/bookmarks.png")));
    bookmarks_->setText(tr("&Marcadores"));



//    QDialog* diag_zoom = new QDialog(this);
//    diag_zoom->setWindowIcon(QIcon(QPixmap(":/icons/resources/main_icon.png")));
//    QGridLayout* layout = new QGridLayout(this);
//    QLabel*  label = new QLabel(("Zoom"),this);
//    QSlider* slZoom = new QSlider((Qt::Orientation::Horizontal),this);

//    slZoom->setRange(0,200);
//    slZoom->setSliderPosition(100);
//    layout->addWidget(label, 0,0,1,1);
//    layout->addWidget(slZoom,1,0,1,1);
//    diag_zoom->setLayout(layout);




    //Configuracion del Layout
    layout_->addWidget(back_,0,0,1,1);
    layout_->addWidget(forward_,0,1,1,1);
    layout_->addWidget(home_,0,2,1,1);
    layout_->addWidget(refresh_,0,3,1,1);
    layout_->addWidget(address_,0,4,1,1);
    layout_->addWidget(bookmarks_,0,5,1,1);
    layout_->addWidget(web_,2,0,1,6);

    //HomePage

    QFile config("./configuracion.txt");

    if(config.open(QIODevice::ReadOnly)){
        QTextStream in(&config);
        homepage_ = in.readLine();
        config.close();
    }

     else
        homepage_ = "http://www.google.es";

    address_->setText(homepage_);
    web_->load(homepage_);
    setLayout(layout_);
    setupConnections();

}

void WebBrowser::setupConnections()
{
    connect(address_,   SIGNAL(returnPressed()),   this,        SLOT(onLoad()));
    connect(refresh_,   SIGNAL(pressed()),         web_,        SLOT(reload()));
    connect(forward_,   SIGNAL(pressed()),         web_,        SLOT(forward()));
    connect(back_,      SIGNAL(pressed()),            web_,     SLOT(back()));
    connect(home_,      SIGNAL(pressed()),            this,     SLOT(onHome()));
    connect(web_,       SIGNAL(urlChanged(QUrl)),      this,    SLOT(onUrlChange(QUrl)));
    connect(web_,       SIGNAL(loadFinished(bool)),    this,    SLOT(onLoadFinished(bool)));
    connect(bookmarks_, &QToolButton::pressed, [&](){           emit marcadores(true,address_->text());   });
    connect(dialogo.lnEdit_, SIGNAL(returnPressed()),   this,   SLOT(onChangeHome()));
//    connect(slZoom,     SIGNAL(valueChanged(int)),      this,   SLOT(onChangeZoom(int)));

}

void WebBrowser::onLoad()
{
    if(!address_->text().startsWith("http://") && !address_->text().startsWith("https://") && address_->text().length()!=0){
        web_->load("http://"+address_->text());
        emit historial(false,"http://"+address_->text());
    }

    else{
           web_->load(address_->text());
            emit historial(false,address_->text());
    }
 }

void WebBrowser::onHome()
{
    address_->setText(homepage_);
    web_->load(homepage_);
}

void WebBrowser::onUrlChange(QUrl url)
{
    address_->setText(url.toString());

}

void WebBrowser::onLoadFinished(bool ok)
{
    if(!ok)
        web_->load("http://duckduckgo.com/?q="+address_->text());

}


void WebBrowser :: onChangeHome(){


    QFile config("./configuracion.txt");

     if(config.open(QIODevice::WriteOnly)){

        homepage_ = dialogo.lnEdit_->text();
        QTextStream out(&config);
        out << homepage_ << endl;

        }
    config.close();
    dialogo.close();
}


//void WebBrowser :: onChangeZoom(int zoom){

//       web_->setZoomFactor(zoom);


//}

