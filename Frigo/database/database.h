#ifndef DATABASE_H
#define DATABASE_H

#include <QDebug>
#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <stdint.h>
#include <string>
#include <memory>

class Database;
typedef std::shared_ptr<Database> database_sptr;

static char *DatabaseName = "FRIGODB";
static char *db_connection="FRIGODB.db3";
static char *db_login="";
static char *db_password="";
static char *db_schema="";
static char *db_type="sqlite";

static database_sptr database_(nullptr);

class Database
{
public:
    static bool init();
    static void release();
    bool isOpen() const;
    static database_sptr getInstance();
    ~Database();

private:
    bool open();
    bool close();
    QSqlDatabase db_;
};

#endif // DATABASE_H
