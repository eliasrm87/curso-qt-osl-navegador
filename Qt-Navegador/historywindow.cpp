#include "historywindow.h"

#include <QGridLayout>
#include <QLabel>
#include <QAction>

HistoryWindow::HistoryWindow(QWidget* parent): URLListDialog(parent) {
  setWindowTitle(tr("Historial"));

  QGridLayout* layout = new QGridLayout(this);
  layout->addWidget(new QLabel(tr("Historial"), this), 0, 0);
  layout->addWidget(list_, 1, 0);

  QAction* actDelete = new QAction(tr("Eliminar"), this);
  actDelete->setShortcut(Qt::Key_Delete);

  connect(actDelete, SIGNAL(triggered()), this, SLOT(onDeleteSelected()));
}

void HistoryWindow::onSaveHistory() {
  // TODO
}
