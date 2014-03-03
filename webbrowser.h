#ifndef WEBBROWSER_H
#define WEBBROWSER_H

#include <QGridLayout>
#include <QWebView>
#include <QLineEdit>
#include <QToolButton>
#include <QWidget>

#include <QTextStream>
#include <QFile>
#include <QMessageBox>
#include <QMenu>
#include <QList>
#include <QAction>
#include <QMenuBar>
#include <QListWidget>

#include <QQuickView>

#include <QTabWidget>

#include <QWebPage>
#include <QPushButton>
#include <QBoxLayout>
class WebBrowser : public QWidget
{
    Q_OBJECT
public:
    explicit WebBrowser(QWidget *parent = 0);

private:
    QWebView *web_;
    QLineEdit *address_;
    QToolButton *refresh_;
    QToolButton *back_;
    QToolButton *forward_;
    QToolButton *home_;
    QGridLayout *layout_;
    QString homepage_;

    QListWidget *listBookmarks_;
    QTextStream *textBookmarks_;

private:
    void setupConnections();
signals:

public slots:
    void onLoad();
    void onHome();
    void onUrlChange(QUrl url);

    void onLoadFinished(bool ok);


    void onBookmarks ();
    void loadBookmark(QListWidgetItem *item);

public:
    void setHomepage();
    void addBookmark();


};

#endif // WEBBROWSER_H
