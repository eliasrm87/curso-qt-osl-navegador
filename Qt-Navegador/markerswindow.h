#ifndef MARKERSWINDOW_H
#define MARKERSWINDOW_H

#include "urllistdialog.h"
#include <QPushButton>

class MarkersWindow: public URLListDialog {
  Q_OBJECT

public:
  explicit MarkersWindow(QWidget *parent = 0);

private:
  QString currentURL_;
  QPushButton* addCurrent_;
  QPushButton* deleteMarker_;
  QPushButton* saveMarkers_;

signals:
  void markersSaved(QList<QString> markers);

public slots:
  void setCurrentURL(QString url);

private slots:
  void onAddCurrent();
  void onSaveMarkers();

};

#endif // MARKERSWINDOW_H
