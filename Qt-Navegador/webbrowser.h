#ifndef WEBBROWSER_H
#define WEBBROWSER_H

#include <QGridLayout>
#include <QWebView>
#include <QLineEdit>
#include <QToolButton>
#include <QMenuBar>
#include <QMenu>
#include <QWidget>
#include <QFile>

class WebBrowser : public QWidget
{
    Q_OBJECT
public:
    explicit WebBrowser(QWidget *parent = 0);

private:
    QMenuBar*       mainMenu_;
    QMenu*          mnuBookmarks_;
    QAction*        actGoToBookmark_;
    QAction*        actmarcador_;
    QWebView        *web_;
    QLineEdit       *address_;
    QToolButton     *refresh_;
    QToolButton     *back_;
    QToolButton     *forward_;
    QToolButton     *home_;
    QToolButton     *addbookmark_;
    QGridLayout     *layout_;
    QString         homepage_;
    QString         bookmarks_file_;
    QString         history_file_;
private:
    void setupConnections();
signals:

public slots:
    void onLoad();
    void onHome();
    void onUrlChange(QUrl url);
    void onLoadFinished(bool ok);
    void addToBookmarks();
    void goToBookmark();
    void refreshBookmarks();

};

#endif // WEBBROWSER_H
