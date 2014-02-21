#include "editarhistorial.h"

editarHistorial::editarHistorial(QWidget *parent) :
    QDialog(parent)
{
    QGridLayout* layoutHist = new QGridLayout;

    QDialogButtonBox* buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
   //  QDialogButtonBox* buttonBox = new QDialogButtonBox(QDialogButtonBox::Cancel);

    QLabel* etiqueta = new QLabel(tr("Clic para borrar del historial"));

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(borrarHistorial()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    layoutHist->addWidget(etiqueta,0,0,1,1);
    layoutHist->addWidget(buttonBox,0,1,1,1);

    QFile file("historial.txt");
    file.open(QIODevice::ReadOnly | QIODevice::Text);

    QTextStream in(&file);
    QString linea = in.readLine();
    QAction* tmpAction;
    int i = 0, j = 0;
    while (!in.atEnd()) {
        linea = in.readLine();
        QCheckBox* address = new QCheckBox(linea.left(25), this);
        layoutHist->addWidget(address,i+5,j,2,1);
        tmpAction = new QAction(linea.left(25), this);
        tmpAction->setData(linea);
        address->addAction(tmpAction);
        connect(address, SIGNAL(clicked(bool)), this, SLOT(borrarHistorial()));
        if (i == 17) {
            j++;
            i = 0;
        }
        else {
            i++;
        }
    }

    setLayout(layoutHist);
    file.close();

}


void editarHistorial::borrarHistorial () {
    //QString linea =  ((QString)QObject::sender()->objectName() );
    QString linea =  ((QString)this->sender()->objectName());
    QMessageBox::about(this, tr("Historial"), linea);
    QFile file("historial.txt");
    file.open(QIODevice::Truncate | QIODevice::Text | QIODevice::ReadWrite);
    file.close();
    this->close();
}
