#include "jactionfavorito.h"

JActionFavorito::JActionFavorito(JActionFavorito *parent) :
    QAction(parent) {
    connect(this, SIGNAL(triggered()), this, SLOT(recibeTriggered()));
}

void JActionFavorito::recibeTriggered() {
  emit pulsado(url_);
}

void JActionFavorito::setURL(QString url) {
  url_ = url;
  setText(url);
}

