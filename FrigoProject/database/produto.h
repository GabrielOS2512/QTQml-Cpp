#ifndef PRODUTO_H
#define PRODUTO_H
#include "database.h"
#include <QSqlTableModel>
#include <QSqlRelationalTableModel>

class Produto;
typedef std::shared_ptr<Produto> produto_sptr ;

class Produto
{
public:
    ///Constructors
    Produto();
    Produto(const QString &nome, const double &valor);
    ///Destructor
    ~Produto() {};

    ///Setters and Getters
    const QString &getId() const { return id_; }

    const QString &getNome() const { return nome_; }
    void setNome(const QString &nome) { nome_ = nome; }

    const double &getValor() const { return valor_; }
    void setValor(const double &valor) { valor_ = valor; }

    ///DB Manipulation
    bool save();
    bool remove();

    ///Query Methods
    static produto_sptr getById(const QString id);
    static std::vector<produto_sptr> getAll();

private:
    QString id_;
    QString nome_;
    double valor_;

    /// internal function to initialize the Produto table
    static bool openTable();

    /// internal function to finish the Produto table
    static bool closeTable();

    /// get a specific produto
    static produto_sptr get(std::string filter);

    /// get multiple produtos
    static std::vector<produto_sptr> get(std::string filter, bool lazy);

    static QSqlRelationalTableModel  *tbProduto_;

};

#endif // PRODUTO_H
