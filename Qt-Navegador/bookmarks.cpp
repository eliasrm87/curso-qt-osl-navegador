#include "bookmarks.h"

bookmarks::bookmarks(QWidget *parent) :
    QWidget(parent)
{
    setMinimumSize(600,300);
    save_ = new QPushButton(tr("Guardar"),this);
    open_ = new QPushButton(tr("Abrir"),this);

    urlSave_ = new QLineEdit(this);

    nameSave_ = new QLineEdit(this);
    nameSave_->setPlaceholderText(tr("Nombre del Marcador"));

    urlOpen_ = new QLineEdit(this);
    urlOpen_->setPlaceholderText(tr("Marcador señalado"));

    list_ = new QListView(this);

    layout_ = new QGridLayout;
    layout_->addWidget(save_,0,0,1,1);
    layout_->addWidget(urlSave_,0,1,1,2);
    layout_->addWidget(nameSave_,1,1,1,2);
    layout_->addWidget(list_,2,0,1,3);
    layout_->addWidget(urlOpen_,3,0,1,2);
    layout_->addWidget(open_,3,2,1,1);

    setLayout(layout_);
    onLoad();

    connect(list_,SIGNAL(clicked(QModelIndex)),this,SLOT(clicked(QModelIndex)));
    connect(open_,SIGNAL(pressed()),this,SLOT(onOpen()));
    connect(save_,SIGNAL(pressed()),this,SLOT(onSave()));
}

void bookmarks::setUrl(QString url)
{
    urlSave_->setText(url);
}

void bookmarks::clicked(const QModelIndex &index)
{
    urlOpen_->setText(urls_[index.row()]);
}

void bookmarks::onSave()
{
    if(settings_ != NULL){
        settings_->setValue("name",nameSave_->text());
        settings_->setValue("url",urlSave_->text());
    }
}

void bookmarks::onOpen()
{
    emit url(urlOpen_->text());
}

void bookmarks::onLoad()
{
    settings_ = new QSettings("/home/nad/bookmarks.ini",QSettings::IniFormat);
    const QStringList childKeys = settings_->allKeys();
    QStringList values;
    foreach (const QString &childKey, childKeys)
        values << settings_->value(childKey).toString();

    for(int i=0; i<(values.size()/2); i++){
        names_.append(values[i]);
        urls_.append(values[i+1]);
    }
    QStringListModel* model = new QStringListModel(this);
    model->setStringList(names_);
    list_->setModel(model);


}
