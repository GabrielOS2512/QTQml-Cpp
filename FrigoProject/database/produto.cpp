#include "produto.h"

#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>

const QString TABLE_PRODUTO = "Produto";
const QString COL_ID = "Codigo";
const QString COL_NOME = "Nome";
const QString COL_VALOR = "Valor";

QSqlRelationalTableModel *Produto::tbProduto_ = 0;

Produto::Produto():id_(), nome_(), valor_()
{
    openTable();
}

Produto::Produto(const QString &nome, const double &valor):id_(), nome_(nome), valor_(valor)
{
    openTable();
}

bool Produto::save()
{
    if(tbProduto_) {
        auto db = Database::getInstance();
        if(!db->getDatabase().transaction()) {
            qDebug() << "Falha ao iniciar Transação: " << db->getDatabase().lastError().text();
            return false;
        }

        if(!getById(id_)) {
            QString strInsert = QString("INSERT INTO %1 (%2, %3) VALUES (?, ?)")
                                .arg(TABLE_PRODUTO, COL_NOME, COL_VALOR);

            QSqlQuery query(Database::getInstance()->getDatabase());
            query.prepare(strInsert);
            query.addBindValue(nome_);
            query.addBindValue(valor_);

            qDebug() << strInsert << nome_ << valor_;

            if (!query.exec()){
                qDebug() << "Produto insert failed: " << query.lastError().text();
                return false;
            }

            return db->getDatabase().commit();
        } else {

        }
    }
    return false;
}

bool Produto::remove()
{
 return false;
}

produto_sptr Produto::getById(const QString id)
{
  return produto_sptr();
}

std::vector<produto_sptr> Produto::getAll()
{
 return std::vector<produto_sptr>();
}

bool Produto::openTable()
{
    if (tbProduto_) return true;

    tbProduto_ = new QSqlRelationalTableModel(nullptr, Database::getInstance()->getDatabase());
    if(tbProduto_) {
        tbProduto_->setTable(TABLE_PRODUTO);
        tbProduto_->setJoinMode(QSqlRelationalTableModel::LeftJoin);
        tbProduto_->setEditStrategy(QSqlTableModel::OnManualSubmit);
        //tbProduto_->setRelation(0,QSqlRelation(TABLE))
        return true;
    }
    qDebug() << "Table Error" << tbProduto_->lastError().text();
    return false;
}

bool Produto::closeTable()
{
    if (tbProduto_){
        delete tbProduto_;
        return true;
    }

    return false;
}

produto_sptr Produto::get(std::string filter)
{
    return produto_sptr();
}

std::vector<produto_sptr> Produto::get(std::string filter, bool lazy)
{
     return std::vector<produto_sptr>();
}
