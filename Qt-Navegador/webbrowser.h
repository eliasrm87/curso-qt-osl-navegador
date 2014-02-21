#ifndef WEBBROWSER_H
#define WEBBROWSER_H

#include <QGridLayout>
#include <QWebView>
#include <QLineEdit>
#include <QToolButton>
#include <QWidget>
#include <QFile>
#include <QTabWidget>


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
    QToolButton* zoomMas_;
    QToolButton* zoomMenos_;
    QToolButton* zoomOriginal_;

private:
    void setupConnections();
signals:

public slots:
    void onLoad();
    void onHome();
    void onUrlChange(QUrl url);

    void onLoadFinished(bool ok);
    void setHistorial();
    void ampliar();
    void reducir();
    void original();


public:
    QLineEdit* getAddress();
    void setAddress(QString linea);
    void setHomePage();
};

#endif // WEBBROWSER_H
