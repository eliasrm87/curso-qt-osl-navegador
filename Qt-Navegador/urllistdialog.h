#ifndef URLLISTDIALOG_H
#define URLLISTDIALOG_H

#include <QDialog>
#include <QList>
#include <QString>
#include <QListWidget>

class URLListDialog: public QDialog {
  Q_OBJECT

public:
  explicit URLListDialog(QWidget *parent = 0);

protected:
  QList<QString> links_;
  QListWidget* list_;

signals:
  void linkLaunched(QString);

public slots:
  void setLinks(QList<QString> markers);

protected slots:
  void onEnter(QListWidgetItem* item);
  void onDeleteSelected();

};

#endif // URLLISTDIALOG_H
