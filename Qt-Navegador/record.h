#ifndef RECORD_H
#define RECORD_H

#include <QFile>
#include <QTextStream>
#include <QDebug>


class Record
{
private:
    QFile *file;
    QString record_name_;
public:
    Record(const QString n_fichero="historial.txt");
    qint16 numline();
    ~Record();

public slots:
    void eraseRecord();
    void addRecord(QString url);
    QString readLine(qint16);

};

#endif // RECORD_H
