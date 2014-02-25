#ifndef WEBBROWSER_H
#define WEBBROWSER_H

#include <QGridLayout>
#include <QWebView>
#include <QLineEdit>
#include <QToolButton>
#include <QWidget>
#include <QAction>
#include <QSettings>
#include <QFile>

class WebBrowser : public QWidget
{
    Q_OBJECT
public:
    explicit WebBrowser(QWidget *parent = 0);

public:
    QWebView*   web_;
    QUrl        urlHistory;

private:
    QLineEdit *address_;
    QToolButton *refresh_;
    QToolButton *back_;
    QToolButton *forward_;
    QToolButton *home_;
    QGridLayout *layout_;
    QSettings settings_;

public:
    QString homepage_;

private:
    void setupConnections();

signals:

public slots:
    void onLoad();
    void onHome();
    void onUrlChange(QUrl url);
    void onLoadFinished(bool ok);
    void setHomepage();

public:
    void setAddress(QString url);
    QString getAddress();
    void loadSettings();
    void saveSettings(QString data);
    void GoHome();
    void addUrlToHistory(QUrl url);
    void addHistoryDinamically(QUrl url);
};

#endif // WEBBROWSER_H
