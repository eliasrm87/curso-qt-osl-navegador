#ifndef HOME_DIALOG_H
#define HOME_DIALOG_H

#include <QDialog>
#include <QGridLayout>
#include <QLineEdit>
#include <QLabel>
#include <QCheckBox>

class home_dialog : public QDialog
{
    Q_OBJECT
public:

    explicit home_dialog(QWidget *parent = 0);
    ~home_dialog();

    QGridLayout*    layout_;
    QLineEdit*      lnEdit_;
    QLabel*         label_;
    QCheckBox*      CheckCookies_;
    QCheckBox*      CheckHistorial_;

signals:

    void newHome(QString);

public slots:


};

#endif // HOME_DIALOG_H
