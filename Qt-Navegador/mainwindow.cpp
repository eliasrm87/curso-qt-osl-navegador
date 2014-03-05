#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    browser_ = new WebBrowser;
    setCentralWidget(browser_);

    // Inicializamos los elementos del menú
    mainMenu_ = new QMenuBar(this);
    mnuNavegador_ = new QMenu(tr("Navegador"), this);
    mnuMarcadores_ = new QMenu(tr("Marcadores"), this);
    mnuMarcadoresVer_ = new QMenu(tr("Ver marcadores"), this);
    mnuHerramientas_ = new QMenu(tr("Herramientas"), this);
    mnuHistorial_ = new QMenu(tr("Historial"), this);
    mnuHistorialVer_ = new QMenu(tr("Ver historial"), this);

    // Inicializamos las acciones
    actNavegadorSalir_ = new QAction(tr("Salir"), this);
    actMarcadoresAgregar_ = new QAction(tr("Agregar marcador"), this);
    actHerramientasHomepage_ = new QAction(tr("Cambiar Homepage"), this);
    actHistorialBorrar_ = new QAction(tr("Borrar historial"), this);

    // Agregamos los menús y las acciones
    mainMenu_->addMenu(mnuNavegador_);
    mnuNavegador_->addAction(actNavegadorSalir_);
    mainMenu_->addMenu(mnuMarcadores_);
    mnuMarcadores_->addAction(actMarcadoresAgregar_);
    mnuMarcadores_->addSeparator();
    mnuMarcadores_->addMenu(mnuMarcadoresVer_);
    mainMenu_->addMenu(mnuHerramientas_);
    mnuHerramientas_->addAction(actHerramientasHomepage_);
    mainMenu_->addMenu(mnuHistorial_);
    mnuHistorial_->addAction(actHistorialBorrar_);
    mnuHistorial_->addSeparator();
    mnuHistorial_->addMenu(mnuHistorialVer_);

    // Conectamos las acciones a los slots
    connect(actNavegadorSalir_, SIGNAL(triggered()), this, SLOT(alSalir()));
    connect(actMarcadoresAgregar_, SIGNAL(triggered()), this, SLOT(alMarcador()));
    connect(actHerramientasHomepage_, SIGNAL(triggered()), this, SLOT(alHomepage()));
    connect(actHistorialBorrar_, SIGNAL(triggered()), this, SLOT(borrarHistorial()));

    // Agregamos el menú al layout
    setMenuBar(mainMenu_);

    // Hacemos que se actualize el historial de forma dinámica
    connect(browser_->getWeb(), SIGNAL(urlChanged(QUrl)), this, SLOT(alHistorial()));
    connect(actHistorialBorrar_, SIGNAL(triggered()), this, SLOT(alHistorial()));
}

MainWindow::~MainWindow()
{

}

void MainWindow::alSalir()
{
    exit(0);
}

void MainWindow::alMarcador()
{
    // TODO: Almacenar marcadores en un .txt

    // Obtenemos el marcador
    QString marcador = browser_->getAddress();

    // Lo añadimos dinámicamente como acción
    QAction *actGoMarcador;
    actGoMarcador = new QAction(marcador, this);
    mnuMarcadoresVer_->addAction(actGoMarcador);
    connect(actGoMarcador, SIGNAL(triggered()), this, SLOT(irMarcador()));
}

void MainWindow::irMarcador()
{

    QAction *accion = (QAction*)QObject::sender();
    browser_->setAddress(accion->text());
}

void MainWindow::alHomepage()
{
    bool aceptar;

    // Recogemos la nueva homepage
    QString nuevaHomepage = QInputDialog::getText(this, tr("Cambiar Homepage"),
                                                  tr("Introduzca la nueva Homepage:"),
                                                  QLineEdit::Normal,
                                                  browser_->getAddress(),
                                                  &aceptar);
    QRegExp whiteSpaces("^\\s+$");

    // Se comprueba que la página no esté vacía
    if (aceptar && !nuevaHomepage.isEmpty() && !whiteSpaces.exactMatch(nuevaHomepage)) {
        browser_->setHomepage(nuevaHomepage);
    }
}

void MainWindow::borrarHistorial()
{
    // Dejamos vacío el fichero del historial
    QFile historial("../historial.txt");
    historial.open(QIODevice::Append | QIODevice::Text);
    historial.resize(0);
    historial.close();

    // Eliminamos las acciones (urls) del menú
    mnuHistorialVer_->clear();
}

void MainWindow::alHistorial()
{
    QFile historial("../historial.txt");

    if (historial.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&historial);
        while (!in.atEnd()) {
            QString url = in.readLine();
            QAction *actGoUrl = new QAction(url, this);
            mnuHistorialVer_->addAction(actGoUrl);

            // Reciclamos el método irMarcador
            connect(actGoUrl, SIGNAL(triggered()), this, SLOT(irMarcador()));
        }
        historial.close();
    }
}
