#include "futebol.h"
#include <chrono>
#include <thread>
#include <QDebug>

Futebol::Futebol(QObject *parent) : QObject(parent)
{
}

void Futebol::iniciarPartida()
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    timeA_ = {"Cruzeiro", 75 , 77, 1.86, 0, 0};
    timeB_ = {"Vasco", 76 , 72, 1.72, 0, 0};
    //int ovrA = ((timeA_.atk + timeA_.def) / 2) * timeA_.tec;
    //int ovrB = ((timeB_.atk + timeB_.def) / 2) * timeB_.tec;
    //qDebug() << ovrA << ovrB;

    for(int t = 0; t < 94; t++) {
        qDebug() << t << ":" << timeA_.nome << timeA_.gols << "x" << timeB_.gols << timeB_.nome;
        if(sorte(calcularChance(timeA_, timeB_))) {
            timeA_.chances++;
            qDebug() << "Chance para o" << timeA_.nome;
            chance(timeA_);
        }
        if(sorte(calcularChance(timeB_, timeA_))) {
            timeB_.chances++;
            qDebug() << "Chance para o" << timeB_.nome;
            chance(timeB_);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(40));
    }
    qDebug() << "Final de Jogo:" << timeA_.nome << timeA_.gols << "x" << timeB_.gols << timeB_.nome;
    qDebug() << "Chances criadas:" << timeA_.nome << timeA_.chances << "-" << timeB_.chances << timeB_.nome;
}

bool Futebol::sorte(int n)
{
    bool res = (std::rand() % 100) < n ? true : false;
    return res;
}

int Futebol::calcularChance(Time ataque, Time defesa)
{
    //Base + influência do ataque e da defesa
    int base_chance = 8;// chance de evento por minuto
    double attack_bonus = (ataque.atk - defesa.def);
    if (attack_bonus + base_chance > 5)
        return attack_bonus + base_chance;
    else
        return 5;
}

void Futebol::chance(Time &time)
{
    int n = std::rand() % 100;
    if(n < 15) {
        qDebug() << "GOL";
        time.gols++;
    } else if (n < 50) {
        qDebug() << "DEFESA";
    } else if (n < 90) {
        qDebug() << "FORA";
    } else {
        qDebug() << "TRAVE";
    }
}
