#ifndef WEBBROWSER_H
#define WEBBROWSER_H

#include <QGridLayout>
#include <QWebView>
#include <QLineEdit>
#include <QToolButton>
#include <QWidget>
#include <QTextStream>
#include <QFile>

#include <QMessageBox>
#include <iostream>
#include <QListWidget>

using namespace std;

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
    QToolButton *z1_;
    QToolButton *z2_;


    QToolButton *marcador_;
//    QAction *direccion_;
//    QMenuBar *fav_;

    QListWidget *lista_;
    QListWidgetItem *item_;
    bool control_;

private:
    void setupConnections();

signals:

public slots:
    void onLoad();
    void onHome(QString cad="");
    void onUrlChange(QUrl url);
    void onLoadFinished(bool ok);

    void marcadores();
    void ir_a(QListWidgetItem *it);
    void zoom1();
    void zoom2();
};

#endif // WEBBROWSER_H
