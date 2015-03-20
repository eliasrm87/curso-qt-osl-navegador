#include "markerswindow.h"

#include <QGridLayout>
#include <QLabel>
#include <QListWidgetItem>

MarkersWindow::MarkersWindow(QWidget *parent): URLListDialog(parent) {
  setWindowTitle(tr("Marcadores"));

  currentURL_ = "about:blank";
  addCurrent_ = new QPushButton(tr("Añadir página actual"), this);
  deleteMarker_ = new QPushButton(tr("Eliminar marcador"), this);
  saveMarkers_ = new QPushButton(tr("Guardar marcadores"), this);

  QGridLayout* layout = new QGridLayout(this);
  layout->addWidget(new QLabel(tr("Marcadores"), this), 0, 0, 1, 3);
  layout->addWidget(list_,                              1, 0, 1, 3);
  layout->addWidget(addCurrent_,                        2, 0, 1, 1);
  layout->addWidget(deleteMarker_,                      2, 1, 1, 1);
  layout->addWidget(saveMarkers_,                       2, 2, 1, 1);

  connect(addCurrent_, SIGNAL(clicked()), this, SLOT(onAddCurrent()));
  connect(deleteMarker_, SIGNAL(clicked()), this, SLOT(onDeleteSelected()));
  connect(saveMarkers_, SIGNAL(clicked()), this, SLOT(onSaveMarkers()));
}

void MarkersWindow::setCurrentURL(QString url) {
  currentURL_ = url.isEmpty()? "about:none" : url;
}

void MarkersWindow::onAddCurrent() {
  links_.append(currentURL_);
  list_->addItem(currentURL_);
}

void MarkersWindow::onSaveMarkers() {
  emit(markersSaved(links_));
}
