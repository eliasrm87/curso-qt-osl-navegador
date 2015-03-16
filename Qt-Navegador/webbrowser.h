#ifndef WEBBROWSER_H
#define WEBBROWSER_H

#include <QGridLayout>
#include <QWebView>
#include <QLineEdit>
#include <QToolButton>
#include <QWidget>
#include<QToolBar>
#include <QMenu>
#include <QMenuBar>
#include <QFile>
#include "home_dialog.hpp"
#include <QSlider>
#include <QCompleter>
#include <QStringList>
#include <QStringListModel>
#include <QWebSettings>

class WebBrowser : public QWidget{

    Q_OBJECT

public:

    explicit WebBrowser(QWidget *parent = 0);
    ~WebBrowser();
private:


    QLineEdit       *address_;
    QToolButton     *refresh_;
    QToolButton     *back_;
    QToolButton     *forward_;
    QToolButton     *home_;
    QToolButton     *bookmarks_;
    QGridLayout     *layout_;
    QString          homepage_;

    QCompleter*     web_Completer;
    QStringList     completer_list;




public:

   bool            delete_historial;
   QWebView        *web_;
   home_dialog       dialogo;

private:

    void setupConnections();
    void startCompleter();
    void onReloadCompleter();
    void Do_Download();

signals:

     void marcadores(bool,QString);
     void historial(bool,QString);
     void name(QString);

public slots:

    void onLoad();
    void onHome();
    void onUrlChange(QUrl url);
    void onLoadFinished(bool ok);
    void onChangeHome();
    void onCookies();
    void onHistorial();
};

#endif // WEBBROWSER_H
