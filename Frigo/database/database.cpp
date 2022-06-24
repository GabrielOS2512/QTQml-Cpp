#include "database.h"

bool Database::init()
{
    if (database_ != nullptr){
        return false;
    }

    database_.reset(new Database());
    if (database_->open()){
        //SystemUserQDB::init(database_);
    }

    return true;
}

void Database::release()
{
    database_.reset();
}

bool Database::isOpen() const
{
    return db_.isOpen();
}

database_sptr Database::getInstance()
{
    return database_;
}

bool Database::open()
{
    if (db_.isOpen()) {
        return false;
    }

    db_ = QSqlDatabase::addDatabase("QSQLITE",DatabaseName);
    db_.setDatabaseName(QString::fromStdString(db_connection));
    if (!db_.open()) {
        qDebug() << "Error opening database: "<< db_connection;
    } else {
        qDebug()<< "Database OK:"<< db_connection;
        return true;
    }

    return false;
}

bool Database::close()
{
    if (db_.isOpen()) {
        db_.close();
        return true;
    }

    return false;
}
