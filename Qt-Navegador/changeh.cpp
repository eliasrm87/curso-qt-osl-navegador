#include "changeh.h"


ChangeH::ChangeH(QWidget *parent) :
    QDialog(parent)
{
   layout_=new QGridLayout();
   setLayout(layout_);
   edit_=new QLineEdit();
   Tbutton_=new QPushButton("OK");
   layout_->addWidget(edit_,0,0,1,1);
   layout_->addWidget(Tbutton_,0,1,1,1);

}
