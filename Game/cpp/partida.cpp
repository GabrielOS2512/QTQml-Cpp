#include "partida.h"
#include <chrono>
#include <thread>
#include <QDebug>

Partida::Partida(QObject *parent) : QObject(parent)
{
}

void Partida::iniciarPartida()
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    placar_[0] = 0;
    placar_[1] = 0;
    //int ovrA = ((timeA_.atk + timeA_.def) / 2) * timeA_.tec;
    //int ovrB = ((timeB_.atk + timeB_.def) / 2) * timeB_.tec;
    //qDebug() << ovrA << ovrB;
    inicializarPartida();

    for(int t = 0; t < 94; t++) {
        qDebug() << t << ":" << timeA_->nome() << timeA_->gols() << "x" << timeB_->gols() << timeB_->nome();
        if(sorte(calcularChance(timeA_, timeB_))) {
            //timeA_.chances++;
            qDebug() << "Chance para o" << timeA_->nome();
            chance(timeA_);
        }
        if(sorte(calcularChance(timeB_, timeA_))) {
            //timeB_.chances++;
            qDebug() << "Chance para o" << timeB_->nome();
            chance(timeB_);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(40));
    }
    qDebug() << "Final de Jogo:" << timeA_->nome() << timeA_->gols() << "x" << timeB_->gols() << timeB_->nome();
    placar_[0] = timeA_->gols();
    placar_[1] = timeB_->gols();
   // qDebug() << "Chances criadas:" << timeA_->nome() << timeA_.chances << "-" << timeB_.chances << timeB_->nome();
}

void Partida::inicializarPartida()
{
    Atributos a = { 75, 77, 1.81};
    Atributos b = { 45, 57, 1.23};
    timeA_.reset(new Time("Cruzeiro", a));
    timeB_.reset(new Time("Ipatinga", b));
}

bool Partida::sorte(int n)
{
    bool res = (std::rand() % 100) < n ? true : false;
    return res;
}

int Partida::calcularChance(time_sptr ataque, time_sptr defesa)
{
    //Base + influência do ataque e da defesa
    int base_chance = 8;// chance de evento por minuto
    double attack_bonus = (ataque->atr().atk - defesa->atr().def);
    if (attack_bonus + base_chance > 4)
        return attack_bonus + base_chance;
    else
        return 4;
}

void Partida::chance(time_sptr time)
{
    int n = std::rand() % 100; // adiciona verificador de atk x def
    if(n < 12) {
        qDebug() << "GOL";
        time->fezGol();
    } else if (n < 25) {
        qDebug() << "PERDEU";
    } else if (n < 45) {
        qDebug() << "DEFENDEU GOLEIRO";
    } else if (n < 75) {
        qDebug() << "DEFESA CORTA";
    } else if (n < 95) {
        qDebug() << "CHUTE PRA FORA";
    } else {
        qDebug() << "BOLA NA TRAVE";
    }
}
