#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    browser_ = new WebBrowser;
    QFile file1("inicio.txt");
    if (file1.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file1);
        if (!in.atEnd()) {
            QString line = in.readLine();
            browser_->setHomepage(line);
        }
        file1.close();
    }
    setCentralWidget(browser_);
    connect (browser_, SIGNAL(favAnadido(QString)), this, SLOT(onFavAnadido(QString)));
    mainMenu_ = new QMenuBar(this);
    mnuFavoritos_ = new QMenu(tr("&Favoritos"), this);
    mainMenu_->addMenu(mnuFavoritos_);
    setMenuBar(mainMenu_);
    listaFav_ = new QList<QString>;

    QFile file("favoritos.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();

            JActionFavorito *nuevoFavorito = new JActionFavorito();
            nuevoFavorito->setURL(line);
            listaFav_->append(line);
            mnuFavoritos_->addAction(nuevoFavorito);
            connect(nuevoFavorito, SIGNAL(pulsado(QString)), browser_, SLOT(irA(QString)));
        }
        file.close();
    }

    pagInicio_ = new QAction(tr("&Cambiar página de inicio"), this);
    mnuOpciones_ = new QMenu(tr("&Opciones"), this);
    mainMenu_->addMenu(mnuOpciones_);
    mnuOpciones_->addAction(pagInicio_);
    connect(pagInicio_, SIGNAL(triggered()), this, SLOT(creaDialogo()));
}

MainWindow::~MainWindow() {
    QFile data("favoritos.txt");
    if (data.open(QFile::WriteOnly | QFile::Truncate)) {
        QTextStream out(&data);
        for (int i = 0; i < listaFav_->size(); i++) {
            out << listaFav_->at(i) << endl;
        }
        data.close();
    }

    QFile data1("inicio.txt");
    if (data1.open(QFile::WriteOnly | QFile::Truncate)) {
        QTextStream out(&data1);
        out << browser_->homepage_ << endl;
        data.close();
    }
}

void MainWindow::onFavAnadido(QString url) {
    QMessageBox dialogo;
    dialogo.setText(url);
    dialogo.exec();
    JActionFavorito *nuevoFavorito = new JActionFavorito();
    nuevoFavorito->setURL(url);
    listaFav_->append(url);
    mnuFavoritos_->addAction(nuevoFavorito);
    connect(nuevoFavorito, SIGNAL(pulsado(QString)), browser_, SLOT(irA(QString)));
}

void MainWindow::creaDialogo() {
    dialogo_ = new JDialogo;
    connect(dialogo_, SIGNAL(pagInicio(QString)), browser_, SLOT(onCmbInicio(QString)));
    dialogo_->exec();
}
