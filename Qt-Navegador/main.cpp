/*
 *  Adrián Rodríguez Bazaga
 *  alu0100826456@ull.edu.es
 *  Navegador web - Curso de QT
 *
 * */

#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QCoreApplication::setOrganizationName("ARB");
    QCoreApplication::setOrganizationDomain("ull.es");
    QCoreApplication::setApplicationName("Navegador Web - ARB");


    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
