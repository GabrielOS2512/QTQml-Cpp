#ifndef FUTEBOL_H
#define FUTEBOL_H

#include <QObject>

struct Time {
    QString nome;
    int atk;
    int def;
    double tec;
    int chances;
    int gols;
};

class Futebol : public QObject
{
    Q_OBJECT
public:
    explicit Futebol(QObject *parent = nullptr);

    enum EVENTO {
        CHANCE,
        GOL,
        FALTA,
        CARTAO
    };

    Q_INVOKABLE void iniciarPartida();

protected:
    bool sorte(int n = 100);
    int calcularChance(Time ataque, Time defesa);
    void chance(Time &time);
    void evento();

private:
    Time timeA_;
    Time timeB_;
};

#endif // FUTEBOL_H
