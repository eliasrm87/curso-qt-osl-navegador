#include "webbrowser.h"

WebBrowser::WebBrowser(QWidget *parent) :
    QWidget(parent)
{
    web_ = new QWebView;

    address_ = new QLineEdit;
    address_->setText(homepage_);

    home_ = new QToolButton;
    homepage_="http://duckduckgo.com";
    web_->load(homepage_);

    refresh_ = new QToolButton;
    refresh_->setIcon(QIcon(QPixmap(":/icons/resources/refresh.png")));

    back_ = new QToolButton;
    back_->setIcon(QIcon(QPixmap(":/icons/resources/go-previous.png")));

    forward_ = new QToolButton;
    forward_->setIcon(QIcon(QPixmap(":/icons/resources/go-next.png")));

    home_->setIcon(QIcon(QPixmap(":/icons/resources/go-home.png")));

    layout_ = new QGridLayout;
    layout_->addWidget(back_,0,0,1,1);
    layout_->addWidget(forward_,0,1,1,1);
    layout_->addWidget(home_,0,2,1,1);
    layout_->addWidget(refresh_,0,3,1,1);
    layout_->addWidget(address_,0,4,1,1);
    layout_->addWidget(web_,1,0,1,5);

    listBookmarks_ = new QListWidget;
    layout_->addWidget(listBookmarks_,1,10,2,2);
    listBookmarks_->setVisible(true);

    setLayout(layout_);
    setupConnections();
    show();
    onBookmarks();
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

void WebBrowser::onBookmarks()
{
    listBookmarks_->clear();
    listBookmarks_->setVisible(true);

    QFile fileBookmarks("/Users/kevinrobayna/Workstation/tmp/qt-browser/bookmarks");
    fileBookmarks.open(QIODevice::ReadOnly | QIODevice::Text);

    QTextStream in(&fileBookmarks);

    while(!in.atEnd())
    {
        QString line = in.readLine();

        listBookmarks_->addItem(new QListWidgetItem(line));

        connect(listBookmarks_,
                SIGNAL( itemClicked ( QListWidgetItem * ) ),
                this,
                SLOT(loadBookmark( QListWidgetItem * ) ) );
    }
    fileBookmarks.close();
}

void WebBrowser::loadBookmark(QListWidgetItem *item)
{
    address_->setText(item->text());
     onLoad();
}

