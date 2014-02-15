#ifndef CHANGEH_H
#define CHANGEH_H

#include <QDialog>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include <QPushButton>

class ChangeH : public QDialog
{
    Q_OBJECT
public:
    explicit ChangeH(QWidget *parent = 0);
    QGridLayout * layout_;
    QLineEdit * edit_;
    QPushButton * Tbutton_;

signals:

public slots:

};

#endif // CHANGEH_H
