#include "record.h"

Record::Record(const QString n_fichero):
    record_name_(n_fichero)
{
    qDebug()<<"Nombre Fichero Historial:"<<n_fichero;
    file = new QFile(record_name_);
}

Record::~Record()
{
    file->close();
}

void Record::eraseRecord()
{
    if (!file->open(QIODevice::Append | QIODevice::Text))
        return;
    file->resize(0);
    file->close();
    //mandar señal limpiar historia de la barra menus
}

void Record::addRecord(QString url)
{
    if (!file->open(QIODevice::Append | QIODevice::Append))
        return;
    QTextStream out(file);
    out << url << "\n";
    file->close();
}

QString Record::readLine(qint16 line)
{
    QString lineString="";
    qint16 i=0;
    if (!file->open(QIODevice::ReadOnly | QIODevice::Text))
        return "-1";

    QTextStream in(file);
    while (i != line) {
        lineString = in.readLine();
        i++;
    }
    file->close();
    return lineString;
}

qint16 Record::numline()
{
    if (!file->open(QIODevice::ReadOnly | QIODevice::Text))
        return -1;
    qint16 contador=0;
    qDebug()<<"Antes de contador.";
    QTextStream in(file);
    while(!in.atEnd()){
        contador++;
    }
    file->close();
    return contador;
}
