#ifndef WEBBROWSER_H
#define WEBBROWSER_H


#include <QGridLayout>
#include <QWebView>
#include <QLineEdit>
#include <QToolButton>
#include <QWidget>
#include <QFile>
class WebBrowser : public QWidget
{
    Q_OBJECT
public:
    explicit WebBrowser(QWidget *parent = 0);

private:
    QWebView *web_;
    QLineEdit *address_;//Añadimos la barra direccion
    QToolButton *refresh_; //Añadimos los botones
    QToolButton *back_;
    QToolButton *forward_;
    QToolButton *home_;
    QGridLayout *layout_;
    QString homepage_;
private:
    void setupConnections();
    void CargarPaginaInicio();
signals:

public slots:
    void onLoad();
    void onHome();
    void onUrlChange(QUrl url);
    void onLoadFinished(bool ok);

public:
    QString getAddress();
    void setAddress(QString linea);
    void setHomePage();
    void AddHistorial();
};

#endif // WEBBROWSER_H
