#ifndef JACTIONFAVORITO_H
#define JACTIONFAVORITO_H

#include <QAction>
#include <QString>

class JActionFavorito : public QAction {
    Q_OBJECT

public:
    explicit JActionFavorito(JActionFavorito *parent = 0);

signals:
    void pulsado (QString url);

public slots:
    void recibeTriggered();

private:
    QString url_;

public:
    void setURL (QString url);

};

#endif // JACTIONFAVORITO_H
