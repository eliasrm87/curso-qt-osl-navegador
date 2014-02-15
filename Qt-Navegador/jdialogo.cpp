#include "jdialogo.h"

JDialogo::JDialogo(QWidget *parent) :
    QDialog(parent) {
    direccion_ = new QLineEdit;
    aceptar_ = new QPushButton("Aceptar", this);
    cancelar_ = new QPushButton("Cancelar", this);
    layout_ = new QGridLayout;

    layout_->addWidget(direccion_, 0, 0, 1, 2);
    layout_->addWidget(aceptar_, 1, 0, 1, 1);
    layout_->addWidget(cancelar_, 1, 1, 1, 1);
    setLayout(layout_);

    connect(aceptar_, SIGNAL(pressed()), this, SLOT(enviaAceptar()));
    connect(aceptar_, SIGNAL(pressed()), this, SLOT(close()));

    connect(direccion_, SIGNAL(returnPressed()), this, SLOT(enviaAceptar()));
    connect(direccion_, SIGNAL(returnPressed()), this, SLOT(close()));

    connect(cancelar_, SIGNAL(pressed()), this, SLOT(close()));

}

void JDialogo::enviaAceptar() {
  emit pagInicio(direccion_->text());
}
