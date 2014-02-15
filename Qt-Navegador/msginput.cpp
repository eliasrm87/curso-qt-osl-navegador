#include "msginput.h"

msgInput::msgInput(QString mensaje, QWidget *parent,) :
    QDialog(parent)
{
    //Primero tiene que salir MENSAJE
    //Luego tiene que tener un sitio para escribir lo que se pida
    //Boton de OK para coger los datos
    //Boton cancel para salir sin recoger dato


   opcion_ = new QLineEdit;
   ok_ = new QToolButton;
   cancel_ = new QToolButton;
   mensaje_ = new QLabel;
   layout_ = new QGridLayout;

   ok_->setText("OK");
   cancel_->setText("Cancel");
   mensaje_->setText(mensaje);

   layout_->addWidget(mensaje_, 0, 0, 1, 2);
   layout_->addWidget(opcion_,  1, 0, 1, 2);
   layout_->addWidget(ok_,      2, 0, 1, 1);
   layout_->addWidget(cancel_,  2, 1, 1, 1);

    //En este caso para lso layouts habria 3 filas(mensaje,opcion,botones) y 2 columas(2   botones)
   //El mensaje ocuparia toda la 1 fila (es decir las dos columnas)
   //La opcion ocuparia toda la 2 fila
   //El boton ok estaria en la 3 fila, 1 columna
   //el boton cancel estaria en la 3 fila 2 columna

   //los dos ultimos valores del layouts seria cuantas filas columnas ocupan

   setLayout(layout_);

   connect(ok_,SIGNAL(pressed()),this,SLOT(alok()));
   connect(cancel_,SIGNAL(pressed()),this,SLOT(close()));
   //connect(opcion_,SIGNAL(returnPressed()),this,SLOT(onDatos()));


   show();


}

void msgInput::alok()
{
    opcion_->text();
    //Falta implementar lo de a donde mando opcion_

    close();
}


