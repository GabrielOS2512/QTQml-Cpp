#include "rodadamodel.h"

int RodadaModel::rowCount(const QModelIndex &parent) const
{
    return rodadaModel_.size();
}

QVariant RodadaModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= rodadaModel_.size())
        return QVariant();

    Partida *p = rodadaModel_.at(index.row());
    switch (role) {
    // case TimeA: return p->timeA_.nome;
    // case TimeB: return p->timeB_.nome;
    // case Placar: return p->getPlacar()[0] + "x" + p->getPlacar()[1];
    // case Tempo: return p->timeA_.nome;
    // case Evento: return p->timeA_.nome;
    }

    return QVariant();
}

QHash<int, QByteArray> RodadaModel::roleNames() const
{
    return {
        { TimeA, "timeA" },
        { TimeB, "timeB" },
        { Placar, "placar" },
        { Tempo, "tempo" },
        { Evento, "evento" }
    };
}
