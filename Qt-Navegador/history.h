#ifndef HISTORY_H
#define HISTORY_H

#include <QWidget>
#include <QWebHistory>
#include <QDebug>
#include <QGridLayout>
#include <QListView>
#include <QStringList>
#include <QStringListModel>

class history : public QWidget
{
    Q_OBJECT
public:
    explicit history(QList<QWebHistoryItem> hist,QWidget *parent = 0);

private:
    QList<QWebHistoryItem> histList_;
    QGridLayout* layout_;

    QListView* list_;
    QStringList items_;

signals:

public slots:

};

#endif // HISTORY_H
