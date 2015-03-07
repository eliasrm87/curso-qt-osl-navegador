#include "markerswindow.h"

#include <QGridLayout>
#include <QLabel>
#include <QListWidgetItem>

MarkersWindow::MarkersWindow(QWidget *parent): QDialog(parent) {
  setWindowTitle(tr("Marcadores"));

  currentURL_ = "about:blank";
  list_ = new QListWidget(this);
  addCurrent_ = new QPushButton(tr("Añadir página actual"), this);
  deleteMarker_ = new QPushButton(tr("Eliminar marcador"), this);
  saveMarkers_ = new QPushButton(tr("Guardar marcadores"), this);

  QGridLayout* layout = new QGridLayout(this);
  layout->addWidget(new QLabel(tr("Marcadores"), this), 0, 0, 1, 3);
  layout->addWidget(list_,                              1, 0, 1, 3);
  layout->addWidget(addCurrent_,                        2, 0, 1, 1);
  layout->addWidget(deleteMarker_,                      2, 1, 1, 1);
  layout->addWidget(saveMarkers_,                       2, 2, 1, 1);

  connect(list_, SIGNAL(itemActivated(QListWidgetItem*)), this, SLOT(onEnter(QListWidgetItem*)));
  connect(addCurrent_, SIGNAL(clicked()), this, SLOT(onAddCurrent()));
  connect(deleteMarker_, SIGNAL(clicked()), this, SLOT(onDeleteSelected()));
  connect(saveMarkers_, SIGNAL(clicked()), this, SLOT(onSaveMarkers()));
}

void MarkersWindow::setCurrentURL(QString url) {
  currentURL_ = url.isEmpty()? "about:none" : url;
}

void MarkersWindow::setMarkers(QList<QString> markers) {
  markers_ = markers;

  list_->clear();
  for (QList<QString>::iterator i = markers.begin(); i != markers.end(); ++i)
    list_->addItem(*i);
}

void MarkersWindow::onEnter(QListWidgetItem* item) {
  emit(markerLaunched(item->text()));
}

void MarkersWindow::onAddCurrent() {
  markers_.append(currentURL_);
  list_->addItem(currentURL_);
}

void MarkersWindow::onDeleteSelected() {
  QListWidgetItem* selectedItm = list_->takeItem(list_->currentRow());
  if (selectedItm)
    markers_.removeOne(selectedItm->text());
}

void MarkersWindow::onSaveMarkers() {
  emit(markersSaved(markers_));
}
