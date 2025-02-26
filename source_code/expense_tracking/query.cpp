#include <QDebug>
#include <QSqlError>

#include "query.h"

/**
 * @brief Constructs a new Query object.
 * @param db The SQL database to use.
 */
Query::Query(const QSqlDatabase& db)
    : QSqlQuery(db)
{}

/**
 * @brief Executes the SQL query.
 * @return True if the query was successful, false otherwise.
 */
bool Query::execute() {
    bool result = exec();
    if(!isActive())
        qDebug() << this->lastError();
    return result;
}
