#ifndef MSGINPUT_H
#define MSGINPUT_H

#include <QDialog>
#include <QLineEdit>
#include <QToolButton>
#include <QGridLayout>
#include <QLabel>


class msgInput : public QDialog
{
    Q_OBJECT
public:
    explicit msgInput(QString mensaje, QWidget *parent = 0);

private:
    QLineEdit *opcion_;
    QToolButton *ok_;
    QToolButton *cancel_;
    QGridLayout *layout_;
    QLabel *mensaje_;

signals:

public slots:
    void alok();
    void onDatos();

};

#endif // MSGINPUT_H
