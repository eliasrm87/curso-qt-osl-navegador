#include "history.h"

history::history(QList<QWebHistoryItem> hist,QWidget *parent) :
    QWidget(parent)
{
    setMinimumSize(600,300);
    setObjectName(tr("Historial"));
    histList_ = hist;
    layout_ = new QGridLayout;
    list_ = new QListView(this);

    foreach(const QWebHistoryItem &item,histList_){
        items_.append(item.title()+":   "+item.url().toString());
    }
    QStringListModel* model = new QStringListModel(this);
    model->setStringList(items_);
    list_->setModel(model);
    list_->setMinimumWidth(600);
    list_->setMinimumHeight(300);
    layout_->addWidget(list_,0,0,1,1);

}
