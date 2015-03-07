#ifndef WEBBROWSER_H
#define WEBBROWSER_H

#include <QGridLayout>
#include <QWebView>
#include <QLineEdit>
#include <QToolButton>
#include <QWidget>
#include <QMenuBar>
#include <QList>
#include <QJsonObject>
#include <QRegExp>
class WebBrowser : public QWidget
{
    Q_OBJECT  //Precompilador de QT
public:
    explicit WebBrowser(QWidget *parent = 0);

private:
    QWebView *web_;
    QLineEdit *address_;
    //QToolButton *refresh_;
    QAction *refresh_;
    //QToolButton *back_;
    QAction *back_;
    //QToolButton *forward_;
    QAction *forward_;
    //QToolButton *home_;
    QAction *home_;
    QGridLayout *layout_;
    QString homepage_;

    QMenuBar       *mainMenu_;
    QJsonObject    jsonMarcador_;
    QMenu          *mnuMarcador_;
    QAction        *aniadirMarcador_;
private:
    void setupConnections();
signals:

public slots:
    void onLoad();
    void onHome();
    void onUrlChange(QUrl url);

    void onLoadFinished(bool ok);
    void marcadores();
};

#endif // WEBBROWSER_H
