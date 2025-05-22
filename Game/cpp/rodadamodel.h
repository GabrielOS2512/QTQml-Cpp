#ifndef RODADAMODEL_H
#define RODADAMODEL_H
#include <QAbstractListModel>
#include "partida.h"

class RodadaModel: public QAbstractListModel {
    Q_OBJECT

public:
    enum PartidaRole {
        TimeA,
        TimeB,
        Placar,
        Tempo,
        Evento
    };
    Q_ENUM(PartidaRole)

    explicit RodadaModel(QObject *parent = nullptr) : QAbstractListModel(parent) {}
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

private:
    QList<Partida*> rodadaModel_;
};

#endif // RODADAMODEL_H
