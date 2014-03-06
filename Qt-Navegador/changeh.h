#ifndef CHANGEH_H
#define CHANGEH_H

#include <QDialog>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include <QPushButton>
#include <QUrl>


class ChangeH : public QDialog
{
    Q_OBJECT
public:
    explicit ChangeH(QWidget *parent = 0);

private:
    QGridLayout * layout_;
    QLineEdit * edit_;
    QPushButton * Tbutton_Aplicar_;
    QPushButton * Tbutton_Cerrar_;



signals:
   void s_change(QUrl);
public slots:
   void change();

};

#endif // CHANGEH_H
