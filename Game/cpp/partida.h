#ifndef PARTIDA_H
#define PARTIDA_H

#include <QObject>
#include "time.h"

class Partida : public QObject
{
    Q_OBJECT

public:
    explicit Partida(QObject *parent = nullptr);

    enum EVENTO {
        CHANCE,
        GOL,
        FALTA,
        CARTAO
    };

    Q_INVOKABLE void iniciarPartida();

    const int* getPlacar() { return placar_; }

private:
    void inicializarPartida();
    bool sorte(int n = 100);
    int calcularChance(time_sptr ataque, time_sptr defesa);
    void chance(time_sptr time);
    void evento();

Q_SIGNALS:
    void placarChanged();

private:
    time_sptr timeA_;
    time_sptr timeB_;

    int placar_[2];
};

#endif // FUTEBOL_H
