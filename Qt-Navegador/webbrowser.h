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
    QLineEdit *address_;
    QToolButton *refresh_;
    QToolButton *back_;
    QToolButton *forward_;
    QToolButton *home_;
    QGridLayout *layout_;
    QString homepage_;

    // Botones de zoom
    QToolButton *moreZoom_;
    QToolButton *lessZoom_;

private:
    void setupConnections();

public slots:
    void onLoad();
    void onHome();
    void onUrlChange(QUrl url);
    void onLoadFinished(bool ok);
    void aumentarZoom();
    void disminuirZoom();

    // Getter y Setter para la URL
    QString getAddress();
    void setAddress(QString address);

    // Getter y Setter para la Homepage
    QString getHomepage();
    void setHomepage(QString homepage);

public:
    void agregarHistorial(QString address);
    QWebView *getWeb();
};

#endif // WEBBROWSER_H
