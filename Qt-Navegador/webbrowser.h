#ifndef WEBBROWSER_H
#define WEBBROWSER_H

#include <QGridLayout>
#include <QWebView>
#include <QLineEdit>
#include <QToolButton>
#include <QWidget>
#include <QMessageBox>
#include <QList>
#include <jdialogo.h>

class WebBrowser : public QWidget {
    Q_OBJECT
public:
    explicit WebBrowser(QWidget *parent = 0);

private:
    //QTextStream para el fichero
    QWebView *web_;
    QLineEdit *address_;
    QToolButton *refresh_;
    QToolButton *back_;
    QToolButton *forward_;
    QToolButton *home_;
    QToolButton *favoritos_;
    QGridLayout *layout_;

public:
    QString homepage_;

private:
    void setupConnections();

signals:
    void favAnadido(QString url);

public slots:
    void setHomepage(QString url);
    void onLoad();
    void onHome();
    void onUrlChange(QUrl url);
    void addFav();
    void onLoadFinished(bool ok);
    void irA(QString url);
    void onCmbInicio(QString url);
};

#endif // WEBBROWSER_H
