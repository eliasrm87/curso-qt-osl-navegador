#ifndef JDIALOGO_H
#define JDIALOGO_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QString>

class JDialogo : public QDialog
{
    Q_OBJECT
public:
    explicit JDialogo(QWidget *parent = 0);

private:
    QLineEdit *direccion_;
    QPushButton *aceptar_;
    QPushButton *cancelar_;
    QGridLayout *layout_;

private slots:
    void enviaAceptar();

signals:
    void pagInicio(QString url);

};

#endif // JDIALOGO_H
