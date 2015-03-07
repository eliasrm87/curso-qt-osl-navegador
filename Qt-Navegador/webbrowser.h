#ifndef WEBBROWSER_H
#define WEBBROWSER_H

#include <QGridLayout>
#include <QWebView>
#include <QLineEdit>
#include <QToolBar>
#include <QAction>
#include <QWidget>

class WebBrowser : public QWidget
{
    Q_OBJECT
public:
    explicit WebBrowser(QWidget *parent = 0);

private:
    QWebView* web_;

    QToolBar* toolbar_;
    QLineEdit* address_;
    QAction* refresh_;
    QAction* back_;
    QAction* forward_;
    QAction* home_;
    QGridLayout* layout_;
    QString homepage_;

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
