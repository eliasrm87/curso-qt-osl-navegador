#include "home_dialog.hpp"
#include <QIcon>
home_dialog::home_dialog(QWidget *parent) : QDialog(parent)
{

   layout_ = new QGridLayout(this);
   label_ = new QLabel(tr("Introduzca la nueva página home"),this);
   lnEdit_ = new QLineEdit(this);
   CheckCookies_ = new QCheckBox(("Permitir Cookies de Terceros"),this);
   CheckHistorial_ = new QCheckBox(("¿Borrar Historial al salir?"),this);

   layout_->addWidget(label_, 0, 0, 1, 1);
   layout_->addWidget(lnEdit_, 1,0, 1, 1);
   layout_->addWidget(CheckCookies_, 2, 0, 1, 1);
   layout_->addWidget(CheckHistorial_, 3, 0, 1, 1);
   this->setWindowIcon(QIcon(QPixmap(":/icons/resources/main_icon.png")));


}

home_dialog::~home_dialog()
{
    layout_->deleteLater();
    lnEdit_->deleteLater();
    label_->deleteLater();
    CheckCookies_->deleteLater();
    CheckHistorial_->deleteLater();
}

