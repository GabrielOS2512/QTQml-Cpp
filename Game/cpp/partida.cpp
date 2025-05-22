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
    placarA_ = 0;
    placarB_ = 0;
    //int ovrA = ((timeA_.atk + timeA_.def) / 2) * timeA_.tec;
    //int ovrB = ((timeB_.atk + timeB_.def) / 2) * timeB_.tec;
    //qDebug() << ovrA << ovrB;
    inicializarPartida();

    for(int t = 0; t < 94; t++) {
        //qDebug() << t << ":" << timeA_->nome() << timeA_->gols() << "x" << timeB_->gols() << timeB_->nome();
        if(sorte(calcularChance(timeA_, timeB_))) {
            //qDebug() << "Chance para o" << timeA_->nome();
            timeA_->chance();
            chance(timeA_, true);
        }
        if(sorte(calcularChance(timeB_, timeA_))) {
            //qDebug() << "Chance para o" << timeB_->nome();
            timeB_->chance();
            chance(timeB_, false);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(40));
    }
    qDebug() << "Final de Jogo:" << timeA_->nome() << timeA_->gols() << "x" << timeB_->gols() << timeB_->nome();
    qDebug() << "Chances criadas:" << timeA_->nome() << timeA_->stats().chances << "-" << timeB_->stats().chances << timeB_->nome();
    qDebug() << "Grandes chances:" << timeA_->nome() << timeA_->stats().grandesChances << "-" << timeB_->stats().grandesChances << timeB_->nome();
    qDebug() << "Chutes a Gol:" << timeA_->nome() << timeA_->stats().chutesGol << "-" << timeB_->stats().chutesGol << timeB_->nome();
    qDebug() << "Defesas Goleiro:" << timeA_->nome() << timeB_->stats().defesas << "-" << timeA_->stats().defesas << timeB_->nome();
}

void Partida::setEvento(QString evt)
{
    evento_ = evt;
    Q_EMIT eventoChanged();
}

void Partida::inicializarPartida()
{
    Atributos a = { 74, 79, 75, 77, 1.81};
    Atributos b = { 65, 57, 59, 69, 1.23};
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
    int base_chance = 6;// chance de evento por minuto
    double attack_bonus = (ataque->atr().atk - defesa->atr().def);
    if (attack_bonus + base_chance > 4)
        return attack_bonus + base_chance;
    else
        return 4;
}

void Partida::chance(time_sptr time, bool isTimeA)
{
    int n = std::rand() % 100; // adicionar verificador de atk x def e outros atributos
    if(n < 10) {
        qDebug() << "GOL";
        time->fezGol();
        time->chuteAGol();
        if(isTimeA) {
            placarA_++;
            Q_EMIT placarAChanged();
        } else {
            placarB_++;
            Q_EMIT placarBChanged();
        }
        setEvento("Gol");
    } else if (n < 30) {
        time->chuteAGol();
        time->defesa();
        setEvento("Defesa do Goleiro");
        qDebug() << "DEFENDEU GOLEIRO";
    } else if (n < 60) {
        qDebug() << "DEFESA CORTA";
        setEvento("Afasta a zaga");
    } else if (n < 95) {
        time->chuteAGol();
        qDebug() << "CHUTE PRA FORA";
        setEvento("Chutou pra fora");
    } else {
        time->chuteAGol();
        time->grandeChance();
        qDebug() << "BOLA NA TRAVE";
        setEvento("Bola na trave!");
    }
}
