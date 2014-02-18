#ifndef WEBBROWSER_H
#define WEBBROWSER_H

#include <QGridLayout>
#include <QWebView>
#include <QLineEdit>
#include <QToolButton>
#include <QWidget>

#include <QTextStream>
#include <QMenu>
#include <QMenuBar>
#include <QWebHistory>
#include <QMessageBox> //Incluido para usarlo como chivato


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

    QToolButton *homedefault_;
    QMenuBar *menu_;
    QMenu *mnuEditar_;
    QAction *actEditarH_;
    QAction *actEditarM_;


private:
    void setupConnections();
signals:

public slots:
    void onLoad();
    void onHome();
    void onUrlChange(QUrl url);

    void onLoadFinished(bool ok);

    void onHomedefault();

    void alHistorial();
};

#endif // WEBBROWSER_H
