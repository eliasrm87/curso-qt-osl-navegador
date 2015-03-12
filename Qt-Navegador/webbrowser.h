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
    ~WebBrowser();

private:
    QList<QString> markerList_;
    QList<QString> historyList_;
    QWebView* web_;

    QToolBar* toolbar_;
    QLineEdit* address_;
    QAction* refresh_;
    QAction* back_;
    QAction* forward_;
    QAction* home_;
    QAction* markers_;
    QAction* config_;
    QAction* history_;
    QGridLayout* layout_;
    QString homepage_;

private:
    void setupConnections();

public slots:
    void onLoad();
    void onHome();

    void onMarkers();
    void onConfiguration();
    void onHistory();

    void onLoadURL(QString url);
    void onUrlChange(QUrl url);
    void onLoadFinished(bool ok);

private slots:
    void setMarkers(QList<QString> markers);
    void setHistory(QList<QString> history);
    void loadMarkers();
    void saveMarkers();
    void loadHistory();
    void saveHistory();

};

#endif // WEBBROWSER_H
