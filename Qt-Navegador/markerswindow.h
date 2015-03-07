#ifndef MARKERSWINDOW_H
#define MARKERSWINDOW_H

#include <QDialog>
#include <QList>
#include <QString>
#include <QListWidget>
#include <QPushButton>

class MarkersWindow : public QDialog
{
  Q_OBJECT

public:
  explicit MarkersWindow(QWidget *parent = 0);

private:
  QString currentURL_;
  QList<QString> markers_;
  QListWidget* list_;
  QPushButton* addCurrent_;
  QPushButton* deleteMarker_;
  QPushButton* saveMarkers_;

signals:
  void markerLaunched(QString);
  void markersSaved(QList<QString> markers);

public slots:
  void setCurrentURL(QString url);
  void setMarkers(QList<QString> markers);

private slots:
  void onEnter(QListWidgetItem* item);
  void onAddCurrent();
  void onDeleteSelected();
  void onSaveMarkers();

};

#endif // MARKERSWINDOW_H
