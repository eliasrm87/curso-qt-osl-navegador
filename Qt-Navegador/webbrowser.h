#ifndef WEBBROWSER_H
#define WEBBROWSER_H

#include <QGridLayout>
#include <QWebView>
#include <QLineEdit>
#include <QToolBar>
#include <QAction>
#include <QWidget>
#include <QContextMenuEvent>

class WebBrowser : public QWidget
{
    Q_OBJECT
public:
    explicit WebBrowser(QWidget *parent = 0);
    ~WebBrowser();

private:
    static const qreal ZOOM_DELTA = 0.1;

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
    QAction* zoomIn_;
    QAction* zoomOut_;
    QGridLayout* layout_;
    QString homepage_;

protected:
    void contextMenuEvent(QContextMenuEvent* ev);

private:
    void setupConnections();

public slots:
    void setMarkers(QList<QString> markers);
    void setHistory(QList<QString> history);
    void setHomepage(QString url);
    void loadMarkers();
    void saveMarkers();
    void loadHistory();
    void saveHistory();

private slots:
    void onLoad();
    void onHome();

    void onMarkers();
    void onConfiguration();
    void onHistory();

    void onLoadURL(QString url);
    void onUrlChange(QUrl url);
    void onLoadFinished(bool ok);

    void onMoreZoom();
    void onLessZoom();
};

#endif // WEBBROWSER_H
