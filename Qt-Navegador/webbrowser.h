#ifndef WEBBROWSER_H
#define WEBBROWSER_H

#include <QGridLayout>
#include <QWebView>
#include <QLineEdit>
#include <QToolButton>
#include <QWidget>
#include <QDialog>
#include <QFile>
class WebBrowser : public QWidget
{
    Q_OBJECT
public:
    explicit WebBrowser(QWidget *parent = 0);
    void pushmarcador();
private:
    QWebView *web_;
    QLineEdit *address_;
    QToolButton *refresh_;
    QToolButton *back_;
    QToolButton *forward_;
    QToolButton *home_;
    QToolButton *marcador_;
    QToolButton *cambiarinicio_;
    QGridLayout *layout_;
    QString homepage_;
    QDialog *dialog_;

private:
    void setupConnections();
signals:
void signalMarcador(QString);
public slots:
    void onLoad();
    void onHome();
    void onUrlChange(QUrl url);
    void marcador();
    void onLoadFinished(bool ok);
    void cargarmarcador(QString);
    QString homepage();
    void changehomepage();
};

#endif // WEBBROWSER_H
