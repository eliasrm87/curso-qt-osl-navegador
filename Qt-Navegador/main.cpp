#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QCoreApplication::setOrganizationName("Skatrak");
    QCoreApplication::setOrganizationDomain("skatrak.com");
    QCoreApplication::setApplicationName("Skatrak Browser");

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
