#ifndef TIME_H
#define TIME_H
#include <QString>
#include <iostream>

struct Atributos {
    int atk;
    int mid;
    int def;
    int glr;
    double tec;
};

struct Stats {
    int chances;
    int chutesGol;
    int defesas;
    int grandesChances;
};
class Time;
typedef std::shared_ptr<Time> time_sptr;

class Time
{
public:
    Time(QString nome, Atributos atr);
    Time(QString nome, Atributos atr, Stats stats);

    QString nome() const;
    void setNome(const QString &newNome);
    Atributos atr() const;
    void setAtr(const Atributos &newAtr);
    Stats stats() const;
    void setStats(const Stats &newStats);
    int gols() const;
    void setGols(int newGols);
    void fezGol();

    void chance();
    void chuteAGol();
    void defesa();
    void grandeChance();

private:
    QString nome_;
    Atributos atr_;
    Stats stats_;
    int gols_=0;

};

#endif // TIME_H
