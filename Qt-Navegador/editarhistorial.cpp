#include "editarhistorial.h"

editarHistorial::editarHistorial(QWidget *parent) :
    QDialog(parent)
{
    layout_ = new QGridLayout;

        layout_ = new QGridLayout;

        QFile file("historial.txt");
        file.open(QIODevice::ReadOnly | QIODevice::Text);

        QTextStream in(&file);
        QString linea = in.readLine();
        int i = 0;
        while (!in.atEnd()) {
            linea = in.readLine();
            QCheckBox* address_ = new QCheckBox;
            address_->setText(linea.left(25));
            layout_->addWidget(address_,i,0,1,1);
            setLayout(layout_);
            i++;
        }
        file.close();

}
