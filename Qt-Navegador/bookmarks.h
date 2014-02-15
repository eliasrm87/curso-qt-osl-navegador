#ifndef BOOKMARKS_H
#define BOOKMARKS_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QGridLayout>
#include <QSettings>
#include <QAction>

#include <QListView>
#include <QStringList>
#include <QStringListModel>

#include <QDebug>
class bookmarks : public QWidget
{
    Q_OBJECT
public:
    explicit bookmarks(QWidget *parent = 0);
    void setUrl(QString);

private:
    QPushButton* save_;
    QPushButton* open_;
    QLineEdit* urlSave_;
    QLineEdit* nameSave_;
    QLineEdit* urlOpen_;

    QListView* list_;
    QStringList names_;
    QStringList urls_;

    QGridLayout* layout_;

    QSettings* settings_;

signals:
    void url(QString url);

private slots:
    void clicked(const QModelIndex & index);

public slots:
    void onSave();
    void onOpen();
    void onLoad();

};

#endif // BOOKMARKS_H
