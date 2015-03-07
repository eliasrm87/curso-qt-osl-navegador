#include "urllistdialog.h"

URLListDialog::URLListDialog(QWidget *parent): QDialog(parent) {
  list_ = new QListWidget(this);

  connect(list_, SIGNAL(itemActivated(QListWidgetItem*)), this, SLOT(onEnter(QListWidgetItem*)));
}

void URLListDialog::setLinks(QList<QString> links) {
  links_ = links;

  list_->clear();
  for (QList<QString>::iterator i = links.begin(); i != links.end(); ++i)
    list_->addItem(*i);
}

void URLListDialog::onEnter(QListWidgetItem* item) {
  emit(linkLaunched(item->text()));
}

void URLListDialog::onDeleteSelected() {
  QListWidgetItem* selectedItm = list_->takeItem(list_->currentRow());
  if (selectedItm)
    links_.removeOne(selectedItm->text());
}
