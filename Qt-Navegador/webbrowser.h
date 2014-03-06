#ifndef WEBBROWSER_H
#define WEBBROWSER_H

#include <QGridLayout>
#include <QWebView>
#include <QLineEdit>
#include <QToolButton>
#include <QWidget>
#include <QTextStream>
#include <QSettings>
#include <QMenu>
#include <QUrl>
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
    QToolButton *marcador_;
    QGridLayout *layout_;
    QString homepage_;
    QSettings settings;

private:
    void setupConnections();
signals:
    void s_marcador(QString);
    void s_historial(QString);
public slots:
    void onLoad();
    void onHome();
    void onUrlChange(QUrl url);
    void guardar_marcador();
    void onLoadFinished(bool ok);
    void set_home_page_s(QUrl ur1);
};

#endif // WEBBROWSER_H
