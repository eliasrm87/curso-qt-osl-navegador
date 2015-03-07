#include "home_dialog.hpp"
#include <QIcon>
home_dialog::home_dialog(QWidget *parent) : QDialog(parent)
{

   layout_ = new QGridLayout(this);
   label_ = new QLabel(tr("Introduzca la nueva página home"),this);
   lnEdit_ = new QLineEdit(this);

   layout_->addWidget(label_, 0, 0, 1, 1);
   layout_->addWidget(lnEdit_, 1,0, 1, 1);

   this->setWindowIcon(QIcon(QPixmap(":/icons/resources/main_icon.png")));


}

home_dialog::~home_dialog()
{

}

