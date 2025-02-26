#ifndef DBSETUP_H
#define DBSETUP_H

#include <QSqlDatabase>

/**
 * @class dbSetup
 * @brief This class is used to setup a database.
 *
 * This class provides functionality to create and remove a database.
 */
class dbSetup
{
    QSqlDatabase db; /**< A QSqlDatabase object representing the database.*/

public:
    /**
     * @brief Constructs a dbSetup object.
     *
     * @param name The name of the database.
     * @param host The host of the database.
     */
    dbSetup(const QString& name, const QString& host);

    /**
     * @brief Destroys the dbSetup object.
     */
    ~dbSetup();

    /**
     * @brief Creates a new database.
     *
     * @return true if the database is created successfully, false otherwise.
     */
    bool createDatabase() const;

    /**
     * @brief Removes an existing database.
     *
     * @return true if the database is removed successfully, false otherwise.
     */
    bool removeDatabase() const;
};

#endif // DBSETUP_H
