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

class WebBrowser : public QWidget{

    Q_OBJECT

public:

    explicit WebBrowser(QWidget *parent = 0);

private:

    QWebView        *web_;
    QLineEdit       *address_;
    QToolButton     *refresh_;
    QToolButton     *back_;
    QToolButton     *forward_;
    QToolButton     *home_;
    QToolButton     *bookmarks_;
    QGridLayout     *layout_;
    QString          homepage_;


//    QGridLayout*    layout;
//    QLabel*         label;
//    QSlider*        slZoom;




public:

//    QDialog*        diag_zoom;
   home_dialog       dialogo;

private:

    void setupConnections();

signals:

     void marcadores(bool,QString);
     void historial(bool,QString);

public slots:

    void onLoad();
    void onHome();
    void onUrlChange(QUrl url);
    void onLoadFinished(bool ok);
    void onChangeHome();
//    void onChangeZoom(int);
};

#endif // WEBBROWSER_H
