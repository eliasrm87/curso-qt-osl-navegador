#ifndef EDITARHISTORIAL_H
#define EDITARHISTORIAL_H

#include <QDialog>
#include <QGridLayout>
#include <QCheckBox>
#include <QTextStream>
#include <QFile>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QLabel>
#include <QAction>
#include <QMessageBox>

class editarHistorial : public QDialog
{
    Q_OBJECT
public:
    explicit editarHistorial(QWidget *parent = 0);

signals:

public slots:

private slots:
    void borrarHistorial();

private:
    QGridLayout* layout_;

};

#endif // EDITARHISTORIAL_H
