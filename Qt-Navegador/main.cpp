#include "mainwindow.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QCoreApplication::setOrganizationName("Igeko");
    QCoreApplication::setOrganizationDomain("igeko.es");
    QCoreApplication::setApplicationName("WebBrowser");


    QApplication a(argc, argv);
    MainWindow w;


    w.setWindowTitle("QBrow");
    w.setWindowIcon(QIcon(QPixmap(":/icons/resources/main_icon.png")));

    w.show();

    return a.exec();
}
