#ifndef WEBBROWSER_H
#define WEBBROWSER_H

#include <QGridLayout>
#include <QWebView>
#include <QLineEdit>
#include <QToolButton>
#include <QWidget>
#include <QFile>

//Este es nuestro navegador que hereda de Qwidget y que se insertará en mainwindow.
class WebBrowser : public QWidget
{
    Q_OBJECT
public:
    explicit WebBrowser(QWidget *parent = 0);

private:
    QWebView *web_; //visor de paǵinas web.
    QLineEdit *address_; //caja de texto donde se escribe la dirección web.
    QToolButton *refresh_;
    QToolButton *back_;
    QToolButton *forward_;
    QToolButton *home_;
    QToolButton *anadirMarcador_;

    QGridLayout *layout_;
    QString homepage_;


private:
    void setupConnections();
signals:
    //Señal que emitirá la URL actual y será emitida desde "onAnadirMarcador()".
    //"mainWindow" capturará esta señal y añadirá la dirección a los marcadores.
    //Hace falta emitir una señal para poder comunicarse entre dos clases.
    void signalAnadirMarcador(QString);

public slots:
    void onLoad();
    void onHome();
    void onUrlChange(QUrl url);        
    void onLoadFinished(bool ok);

    void onAnadirMarcador();

public:
    void goTo(QString URL);
};

#endif // WEBBROWSER_H
