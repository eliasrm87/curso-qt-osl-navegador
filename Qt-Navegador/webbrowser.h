#ifndef WEBBROWSER_H
#define WEBBROWSER_H

#include <QGridLayout>
#include <QWebView>
#include <QLineEdit>
#include <QToolButton>
#include <QWidget>
#include <QSettings>

class WebBrowser : public QWidget
{
    Q_OBJECT //directiva al prepocesador de QT, primero lo convierten a c++ y luego lo precomplian en QT.

private:
    QWebView *web_;
    QLineEdit *address_;
    QToolButton *refresh_;
    QToolButton *back_;
    QToolButton *forward_;
    QToolButton *home_;
    QGridLayout *layout_;
    QString homepage_;

private:
    void setupConnections();
    void Icon();
    void DrawIcon();

public:
    explicit WebBrowser(QWidget *parent = 0);
    QString get_homepage();
    void set_homepage(QString);
    void load();
    QWebView *getWeb();

public slots:
    void onLoad();
    void onHome();
    void onUrlChange(QUrl url);
    void AcercarZoom();
    void AlejarZoom();
    void onLoadFinished(bool ok);
    QString getAddress();
    void setAddress(QString);
};

#endif // WEBBROWSER_H
