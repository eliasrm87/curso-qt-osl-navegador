#include "changehp.h"

ChangeHP::ChangeHP(QWidget *parent) :
    QDialog(parent)
{
    layout_= new QGridLayout;
    this->setLayout(layout_);

    barra_ = new QLineEdit;
    barra_->setPlaceholderText("Cambiar Pagina de Inicio");
    layout_->addWidget(barra_,0,0,1,3);

    botonGuardar_ = new QPushButton("Guardar");
    layout_->addWidget(botonGuardar_,1,1,1,1);

    botonCancelar_ = new QPushButton("Cancelar");
    layout_->addWidget(botonCancelar_,1,2,1,1);

    connect (botonCancelar_, SIGNAL(pressed()),this, SLOT(close()));
    connect (botonGuardar_, SIGNAL(pressed()),this, SLOT(guardarHP()));
}

void ChangeHP::guardarHP()
{
   emit HomePage(QUrl(barra_->text()));
}
