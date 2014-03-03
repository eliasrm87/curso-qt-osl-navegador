#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "webbrowser.h"
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    WebBrowser *browser_;

    QMenuBar *mainMenu_;

    QMenu *menuBookmark_;
    QAction *actionAddBookmark_;

    QMenu *menuHomepage_;
    QAction *actionSetHomepage_;

private slots:
    void addBookmark();
    void setAsHomepage();
};

#endif // MAINWINDOW_H
