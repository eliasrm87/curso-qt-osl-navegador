#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    browser_ = new WebBrowser;
    setCentralWidget(browser_);

    this->mainMenu_ = new QMenuBar(this);

    this->menuBookmark_ = new QMenu("Bookmarks",  this);
    this->menuHomepage_ = new QMenu("Homepage", this);

    this->mainMenu_->addMenu(menuBookmark_);
    this->mainMenu_->addMenu(menuHomepage_);

    this->actionAddBookmark_    = new QAction("Add To Bookmarks", this);
    this->actionSetHomepage_    = new QAction("Set as Homepage", this);

    this->menuBookmark_->addAction(actionAddBookmark_);
    this->menuHomepage_->addAction(actionSetHomepage_);

    this->setMenuBar(mainMenu_);

    connect(actionAddBookmark_,SIGNAL(triggered()), this, SLOT(addBookmark()));
    connect(actionSetHomepage_,SIGNAL(triggered()), this, SLOT(setAsHomepage()));
}

MainWindow::~MainWindow()
{

}

void MainWindow::addBookmark()
{
    this->browser_->addBookmark();
}

void MainWindow::setAsHomepage()
{
    this->browser_->setHomepage();
}
