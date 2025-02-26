#include <QSqlQuery>
#include <QSqlError>

#include "dbsetup.h"

dbSetup::dbSetup(const QString& database, const QString& connection)
{
    db = QSqlDatabase::addDatabase("QMYSQL", connection);
    db.setHostName("<db_host>");
    db.setDatabaseName(database);
    db.setUserName("<db_user>");
    db.setPassword("<db_password>");
    if(!db.open())
        qDebug() << "Erreur: database";
}

dbSetup::~dbSetup()
{
    db.close();
}

bool dbSetup::createDatabase() const
{
    QSqlQuery query(db);

    query.exec("CREATE TABLE IF NOT EXISTS ETUser ("
               "username VARCHAR(150) NOT NULL,"
               "password TEXT NOT NULL,"
               "birth DATE NOT NULL,"
               "email TEXT NOT NULL,"
               "gender ENUM('m', 'f'),"
               "budget REAL NOT NULL,"
               "auth_attempt INT NOT NULL,"
               "last_auth_attempt TIMESTAMP DEFAULT NULL,"
               "PRIMARY KEY (username)"
               ");");

    query.exec("CREATE TABLE IF NOT EXISTS Reminder ("
               "id_rem SERIAL PRIMARY KEY,"
               "name_rem TEXT NOT NULL,"
               "date_rem DATE NOT NULL,"
               "user VARCHAR(150) NOT NULL,"
               "FOREIGN KEY (user) REFERENCES ETUser(username)"
               ");");

    query.exec("CREATE TABLE IF NOT EXISTS Category ("
               "id_cat SERIAL PRIMARY KEY,"
               "name_cat TEXT NOT NULL,"
               "color TEXT NOT NULL,"
               "user VARCHAR(150) NOT NULL,"
               "FOREIGN KEY (user) REFERENCES ETUser(username)"
               ");");

    query.exec("CREATE TABLE IF NOT EXISTS Expense ("
               "id_exp SERIAL PRIMARY KEY,"
               "name_exp TEXT NOT NULL,"
               "desc_exp TEXT NOT NULL,"
               "date_exp DATE NOT NULL,"
               "value_exp REAL NOT NULL,"
               "cat_exp BIGINT UNSIGNED,"
               "user VARCHAR(150) NOT NULL,"
               "FOREIGN KEY (cat_exp) REFERENCES Category(id_cat),"
               "FOREIGN KEY (user) REFERENCES ETUser(username)"
               ");");

    if(query.lastError().isValid()) {
        qDebug() << "Erreur lors de la création de la base de données : " << query.lastError().text();
        return false;
    }

    return true;
}

bool dbSetup::removeDatabase() const
{
    QSqlQuery query(db);

    query.exec("DROP TABLE IF EXISTS Expense;");
    query.exec("DROP TABLE IF EXISTS Category;");
    query.exec("DROP TABLE IF EXISTS Reminder;");
    query.exec("DROP TABLE IF EXISTS ETUser;");

    if(query.lastError().isValid()) {
        qDebug() << "Erreur lors de la suppression de la base de données : " << query.lastError().text();
        return false;
    }

    return true;
}
