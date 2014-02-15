#ifndef WEBBROWSER_H
#define WEBBROWSER_H

#include <QGridLayout>
#include <QWebView>
#include <QLineEdit>
#include <QToolButton>
#include <QWidget>
#include <QLineEdit>
#include <QSettings>

class WebBrowser : public QWidget
{
    Q_OBJECT
public:
    explicit WebBrowser(QWidget *parent = 0);
    QString getAddress();
    void setAddress(QString url);
    void setHomeAddress(QString url);
    void loadSettings();
    void saveSettings(QString data);
    void GoHome();

private:
    QWebView *web_;
    QLineEdit *address_;
    QToolButton *refresh_;
    QToolButton *back_;
    QToolButton *forward_;
    QToolButton *home_;
    QGridLayout *layout_;
    QString homepage_;
    QSettings settings_; // Configuraciones
private:
    void setupConnections();
signals:

public slots:
    void onLoad();
    void onHome();
    void onUrlChange(QUrl url);

    void onLoadFinished(bool ok);
};

#endif // WEBBROWSER_H
