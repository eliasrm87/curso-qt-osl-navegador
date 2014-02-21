#ifndef WEBBROWSER_H
#define WEBBROWSER_H

#include <QGridLayout>
#include <QWebView>
#include <QLineEdit>
#include <QToolButton>
#include <QWidget>
#include <QVector>
#include <QAction>

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
    QGridLayout *layout_;
    QString homepage_;
    //Por mi
    QToolButton *marcadores_;
    QVector<QString> listaMarcadores_;
    QVector<QString> listaNameMarcadores_;
    QToolButton *inicio_;
    QVector<QString> historial_;


private:
    void setupConnections();
signals:

public slots:
    void onLoad();
    //Por mi-----
    void onLoad2();
    //--------
    void onHome();
    void onUrlChange(QUrl url);

    void onLoadFinished(bool ok);
    //Por mi

    void onMarcador();
    void onInicio();

public:
    int get_tamMarcadores();
    QString get_marcador(int i);
    QString get_nameMarcador(int i);
    void set_inicialPage(QString pagina);
    QString get_historial(int i);
    int tam_historial();
    void delete_historial(int i);
signals:
   void sMarcador(void);
};

#endif // WEBBROWSER_H
