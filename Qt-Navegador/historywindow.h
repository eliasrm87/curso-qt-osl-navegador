#ifndef HISTORYWINDOW_H
#define HISTORYWINDOW_H

#include "urllistdialog.h"
#include <QWebHistory>

class HistoryWindow: public URLListDialog {
  Q_OBJECT

public:
  explicit HistoryWindow(QWidget* parent = 0);
  ~HistoryWindow();

signals:
  void historySaved(QList<QString> markers);

private slots:
  void onSaveHistory();

};

#endif // HISTORYWINDOW_H
