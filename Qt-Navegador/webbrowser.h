#ifndef WEBBROWSER_H
#define WEBBROWSER_H

#include <QGridLayout>
#include <QWebView>
#include <QLineEdit>
#include <QToolButton>
#include <QWidget>
#include <QFileDialog>
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
    QToolButton *addMarcador_;
    QToolButton *marcador_;
    QGridLayout *layout_;
    QString homepage_;
private:
    void setupConnections();
signals:
    void signalMarcador(QString);

public slots:
    void onLoad();
    void emitirMarcador();
    void onHome();
    void onUrlChange(QUrl url);
    void onLoadFinished(bool ok);
public:
    void goTo(QString url);


};

#endif // WEBBROWSER_H
