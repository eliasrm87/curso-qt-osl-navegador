#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    browser_ = new WebBrowser;
    setCentralWidget(browser_);

    mainmenu_= new QMenuBar(this);


    marcadores_ = new QMenu(tr("&Marcadores"),this);
    mainmenu_->addMenu((marcadores_));

    setMenuBar(mainmenu_);

    QFile archivo;
    archivo.setFileName("marcadores.txt");
    if(archivo.open(QFile::ReadOnly))
    {
        QAction* act;
        QTextStream textStream(&archivo);
        while(!textStream.atEnd()){
           QString line = textStream.readLine();
           act= new QAction(line,this);
           marcadores_->addAction(act);
           connect(act ,SIGNAL(triggered()),this,SLOT(onmarcador()));
        }
        archivo.close();
    }
     connect(browser_ ,SIGNAL(signalMarcador(QString)),this,SLOT(guardarmarcador(QString)));



}
void MainWindow::guardarmarcador(QString url){
    QAction* marcador=marcadores_->addAction(url);
    connect(marcador, SIGNAL(triggered()), this, SLOT(onMarcador()));
            QFile archivo;
            archivo.setFileName("marcadores.txt");
             if(archivo.open(QFile::ReadWrite))
             {
              QTextStream out(&archivo);
              out<<url<<endl;
              archivo.close();
             }
}
void MainWindow::change(QString url){

}

void MainWindow::onmarcador(){
//     QAction* act = (QAction*) QObject::sender();


}



MainWindow::~MainWindow()
{

}
