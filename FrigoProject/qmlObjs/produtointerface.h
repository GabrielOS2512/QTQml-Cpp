#ifndef PRODUTOINTERFACE_H
#define PRODUTOINTERFACE_H

#include "database/produto.h"
#include <QObject>

class ProdutoInterface : public QObject
{
    Q_OBJECT
public:
    explicit ProdutoInterface(QObject *parent = nullptr);
};

#endif // PRODUTOINTERFACE_H
