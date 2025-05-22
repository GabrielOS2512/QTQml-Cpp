#ifndef PARTIDA_H
#define PARTIDA_H

#include <QObject>
#include "time.h"

class Partida : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int placarA READ placarA NOTIFY placarAChanged)
    Q_PROPERTY(int placarB READ placarB NOTIFY placarBChanged)
    Q_PROPERTY(QString evento READ evento NOTIFY eventoChanged)

public:
    explicit Partida(QObject *parent = nullptr);

    enum EVENTO {
        CHANCE,
        GOL,
        FALTA,
        CARTAO
    };

    Q_INVOKABLE void iniciarPartida();

    QString evento() { return evento_; }
    void setEvento(QString evt);
    const int placarA() { return placarA_; }
    const int placarB() { return placarB_; }

private:
    void inicializarPartida();
    bool sorte(int n = 100);
    int calcularChance(time_sptr ataque, time_sptr defesa);
    void chance(time_sptr time, bool isTimeA = true);

Q_SIGNALS:
    void placarAChanged();
    void placarBChanged();
    void eventoChanged();

private:
    time_sptr timeA_;
    time_sptr timeB_;

    int placarA_ = 0;
    int placarB_ = 0;
    QString evento_ = "";
};

#endif // FUTEBOL_H
