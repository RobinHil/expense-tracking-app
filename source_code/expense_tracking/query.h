#ifndef QUERY_H
#define QUERY_H

#include <QSqlQuery>
#include <QSqlDatabase>

/**
 * @brief Class representing a SQL query.
 */
class Query : public QSqlQuery {
public:
    /**
     * @brief Constructs a new Query object.
     * @param db The SQL database to use.
     */
    Query(const QSqlDatabase& db);

    /**
     * @brief Executes the SQL query.
     * @return True if the query was successful, false otherwise.
     */
    bool execute();
};

#endif // QUERY_H
