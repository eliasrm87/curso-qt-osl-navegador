#include "configurationwindow.h"

#include <QLabel>
#include <QGridLayout>

ConfigurationWindow::ConfigurationWindow(const QString& homepage, QWidget *parent): QDialog(parent) {
  setWindowTitle(tr("Configuración"));

  ok_ = new QPushButton(tr("Aceptar"), this);
  cancel_ = new QPushButton(tr("Cancelar"), this);
  homepage_ = new QLineEdit(homepage, this);

  QGridLayout* layout = new QGridLayout(this);
  layout->addWidget(new QLabel(tr("Página de inicio"), this), 0, 0, 1, 1);
  layout->addWidget(homepage_,                                0, 1, 1, 1);
  layout->addWidget(ok_,                                      1, 0, 1, 1);
  layout->addWidget(cancel_,                                  1, 1, 1, 1);

  connect(ok_, SIGNAL(clicked()), this, SLOT(onSaveHomepage()));
  connect(ok_, SIGNAL(clicked()), this, SLOT(close()));
  connect(cancel_, SIGNAL(clicked()), this, SLOT(close()));
}

void ConfigurationWindow::onSaveHomepage() {
    emit(homepageSaved(homepage_->text()));
}
