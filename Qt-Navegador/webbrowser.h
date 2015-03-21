#ifndef WEBBROWSER_H
#define WEBBROWSER_H

#include <QGridLayout>
#include <QWebView>
#include <QLineEdit>
#include <QToolButton>
#include <QWidget>
#include <QMenuBar>
#include <QMenu>
#include <QToolBar>
#include <QApplication>
#include <QListWidget>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QInputDialog>

class WebBrowser : public QWidget
{
    Q_OBJECT
public:
    explicit WebBrowser(QWidget *parent = 0);

private:
    QMenuBar*       mainMenu_;
    QMenu*          mnuArchivo_;
    QMenu*          mnuMarcadores_;
    QMenu*          mnuHistorial_;
    QAction*        actArchivoHome_;
    QAction*        actArchivoSalir_;
    QAction*        actGoogle_;
    QListWidget *lista_marcadores_;
    QWebView *web_;
    QLineEdit *address_;
    QToolButton *refresh_;
    QToolButton *back_;
    QToolButton *forward_;
    QToolButton *home_;
    QToolButton *addBookmark_;
    QToolButton *zoom_;
    QToolButton *zoomin_;
    QToolButton *zoomout_;
    QToolButton *add_;
    QGridLayout *layout_;
    QString homepage_;
    QWebView *brow_;
    QVBoxLayout *caja_;
    QTabWidget *tab_;
    QTabBar *tabi_;
    QPushButton *cerrar_;

private:
    void setupConnections();
signals:

public slots:
    void onLoad();
    void onQuit();
    void onHome();
    void onAddBMark();
    void onUrlChange(QUrl url);
    void onLoadFinished(bool ok);
    void onBookmark();
    void onAmpliar();
    void onReducir();
    void onOriginal();
    void onDefinirHome();
    void getHome();
    void nueva_ventana();
    void cerrar_nueva_ventana();
    void contextMenuRequested(QAction *d);
};

#endif // WEBBROWSER_H
