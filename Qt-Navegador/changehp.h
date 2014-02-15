#ifndef CHANGEHP_H
#define CHANGEHP_H

#include <QDialog>
#include <QLayout>
#include <QPushButton>
#include <QLineEdit>

class ChangeHP : public QDialog
{
    Q_OBJECT
public:
    explicit ChangeHP(QWidget *parent = 0);

signals:
    void HomePage(QUrl url);

private:
    QGridLayout *layout_;
    QPushButton *botonGuardar_;
    QPushButton *botonCancelar_;
    QLineEdit *barra_;

public slots:
    void guardarHP();

};

#endif // CHANGEHP_H
