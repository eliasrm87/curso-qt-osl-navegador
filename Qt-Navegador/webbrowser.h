#ifndef WEBBROWSER_H
#define WEBBROWSER_H

#include <QGridLayout>
#include <QWebView>
#include <QLineEdit>
#include <QToolButton>
#include <QWidget>

//
#include <QTextStream>
#include <QFile>
#include <QMessageBox>
#include <QMenu>
#include <QList>
#include <QAction>
#include <QMenuBar>
#include <QListWidget>


#include <QQuickView>

#include <QTabWidget>

#include <QWebPage>
#include <QPushButton>
#include <QBoxLayout>


class WebBrowser : public QWidget
{
    Q_OBJECT
public:
    explicit WebBrowser(QWidget *parent = 0);

private:
    QWebView *web_;
    QLineEdit *address_;

    //para poner nuestros iconos
    QToolButton *refresh_;
    QToolButton *back_;
    QToolButton *forward_;
    QToolButton *home_;

    QToolButton *botonmarcador_;
    QToolButton *botoncerrarmarcadores_;

    QToolButton *botonpaginanueva_;

    //botones del zoom
    QToolButton *boton_ampliar_zoom_;
    QToolButton *boton_reducir_zoom_;

    //colocar los elementos en el main window
    QGridLayout *layout_;
    QString homepage_;

    //fichero para almacenar los marcadores
    QTextStream *texto_;
    QMenuBar *marcador_;

    QAction *direc_;

    QListWidget *lista_marcadores_;


    //funcionalidad nueva ventana
    QWebView *brow_;
    QBoxLayout *caja_;
    QTabWidget *tab_;
    QTabBar *tabi_;
    QPushButton *cerrar_;



private:
    void setupConnections();
signals:

public slots:
    void onLoad();
    void onHome();
    void onUrlChange(QUrl url);

    void onLoadFinished(bool ok);

    //marcadores
    void marcadores();
    void cargarpagina(QListWidgetItem *item);
    void cerrar_marcadores();
    void nueva_ventana();
    void cerrar_nueva_ventana();
    void ampliar_zoom();
    void reducir_zoom();
};

#endif // WEBBROWSER_H
