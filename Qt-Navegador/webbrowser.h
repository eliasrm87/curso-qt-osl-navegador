#ifndef WEBBROWSER_H
#define WEBBROWSER_H

#include <QGridLayout>
#include <QWebView>//Visualizacion de la web en sí misma
#include <QLineEdit>//Para meter las URL's
#include <QToolButton>//Facilita el hecho de poner iconos
#include <QWidget>
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
    //----
    QToolButton *bookmarks_;
    //----
    QGridLayout *layout_;
    QString homepage_;
private:
    void setupConnections();
signals:

public slots:
    void onLoad();
    void onHome();
    void onUrlChange(QUrl url);

    void onLoadFinished(bool ok);
};

#endif // WEBBROWSER_H
