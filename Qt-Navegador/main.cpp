#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

/*
 * int const MainWindow::EXIT_CODE_REBOOT = -123456789;
 * int currentExitCode = 0;
 * do{
  }while(currentExitCode == MainWindow::EXIT_CODE_REBOOT);
*/
