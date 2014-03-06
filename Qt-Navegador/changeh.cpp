#include "changeh.h"


ChangeH::ChangeH(QWidget *parent) :
    QDialog(parent)
{
   layout_=new QGridLayout();
   setLayout(layout_);
   edit_=new QLineEdit();
   Tbutton_Aplicar_=new QPushButton("Aplicar");
   Tbutton_Cerrar_ = new QPushButton("Cancelar");
   layout_->addWidget(edit_,0,0,1,1);
   layout_->addWidget(Tbutton_Aplicar_,0,1,1,1);
   layout_->addWidget(Tbutton_Cerrar_,0,2,1,1);
   connect(Tbutton_Aplicar_,SIGNAL(pressed()),this,SLOT(change()));
   connect(Tbutton_Cerrar_, SIGNAL(pressed()),this, SLOT(close()));


}

void ChangeH::change()
{
    emit s_change(QUrl(edit_->text()));
    close();
}
