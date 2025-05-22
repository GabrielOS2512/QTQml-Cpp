#include "time.h"

Time::Time(QString nome, Atributos atr) :
    nome_(nome),
    atr_(atr)
{
    stats_ = { 0, 0, 0, 0};
}

Time::Time(QString nome, Atributos atr, Stats stats) :
    nome_(nome),
    atr_(atr),
    stats_(stats)
{

}

QString Time::nome() const
{
    return nome_;
}

void Time::setNome(const QString &newNome)
{
    nome_ = newNome;
}

Atributos Time::atr() const
{
    return atr_;
}

void Time::setAtr(const Atributos &newAtr)
{
    atr_ = newAtr;
}

Stats Time::stats() const
{
    return stats_;
}

void Time::setStats(const Stats &newStats)
{
    stats_ = newStats;
}

int Time::gols() const
{
    return gols_;
}

void Time::setGols(int newGols)
{
    gols_ = newGols;
}

void Time::fezGol()
{
    gols_++;
}

void Time::chance()
{
    stats_.chances++;
}

void Time::chuteAGol()
{
    stats_.chutesGol++;
}

void Time::defesa()
{
    stats_.defesas++;
}

void Time::grandeChance()
{
    stats_.grandesChances++;
}
