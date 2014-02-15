#include "changeh.h"


ChangeH::ChangeH(QWidget *parent) :
    QDialog(parent)
{
   layout_=new QGridLayout();
   setLayout(layout_);
   edit_=new QLineEdit();
   Tbutton_=new QPushButton("Aplicar");
   layout_->addWidget(edit_,0,0,1,1);
   layout_->addWidget(Tbutton_,0,1,1,1);
   connect(Tbutton_,SIGNAL(pressed()),this,SLOT(change()));

}

void ChangeH::change()
{
    home=edit_->text();
    emit s_change(edit_->text());
}
