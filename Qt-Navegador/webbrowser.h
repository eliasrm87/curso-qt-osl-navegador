#ifndef WEBBROWSER_H
#define WEBBROWSER_H

#include <QGridLayout>
#include <QWebView>
#include <QLineEdit>
#include <QToolButton>
#include <QWidget>
#include <QMenu>
#include <QAction>

class WebBrowser : public QWidget
{
    Q_OBJECT
public:
    explicit WebBrowser(QWidget *parent = 0);

private:
    QWebView *web_; //Se utiliza para visualizar las paginas
    QLineEdit *address_; //Entrada de texto para las direcciones
    QToolButton *refresh_; //Los botones ToolButton porque nos permite poner iconos
    QToolButton *back_;
    QToolButton *forward_;
    QToolButton *marcador_; //Boton para el marcador
    QToolButton *home_;
    QGridLayout *layout_;
    QString homepage_;


private:
    void setupConnections();

signals:
    void smarcador(QString url);

private slots:
    void onMarcador();

public slots:
    void onLoad();
    void onHome();
    void onUrlChange(QUrl url);
    void onLoadFinished(bool ok);
    void ObtenerUrl(QUrl);
public:
    QString address();
};

#endif // WEBBROWSER_H
