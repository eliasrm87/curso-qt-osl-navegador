/*
 *  Adrián Rodríguez Bazaga
 *  alu0100826456@ull.edu.es
 *  Navegador web - Curso de QT
 *
 * */

#ifndef WEBBROWSER_H
#define WEBBROWSER_H


#include <QGridLayout>
#include <QWebView>
#include <QMainWindow>
#include <QLineEdit>
#include <QToolButton>
#include <QWidget>
#include <QFile>
#include <QTabWidget>
#include <QTabBar>
#include <QPushButton>
#include <QStandardItemModel>
#include <QTreeView>
#include <QMenu>

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
    //Zoom
    QToolButton* Ampliar_;
    QToolButton* Reducir_;
    QToolButton* Original_;
    //
    //Pestañas
    QToolButton *ventanaAdd_;
    QTabWidget *tab_;
    //
    //Menu contextual
    QMenu* contextMenu;
    QAction* actCM1;
    QAction* actCM2;
    QAction* actCM3;
    //
    QGridLayout *layout_;
    QString homepage_;
private:
    void setupConnections();
signals:
    void signalRB();
public:
    QLineEdit* getAddress();
    void setAddress(QString linea);
    void setHomePage();


public slots:
    void onLoad();
    void onHome();
    void onUrlChange(QUrl url);

    //Zoom
    void onAmpliar();
    void onReducir();
    void onOriginal();
    //
    //Pestañas
    void onNuevaVentana();
    void onCerrarVentana(int);
    void onTabCambia(int);
    //

    //Menu contextual
    void contextMenuRequested(QPoint point);
    //

    void onLoadFinished(bool ok);
};

#endif // WEBBROWSER_H
