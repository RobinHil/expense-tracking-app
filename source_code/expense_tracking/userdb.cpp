#include "userdb.h"
#include "query.h"

/**
 * @brief UserDB::UserDB creates an instance of UserDB class.
 * It opens a connection to the database to manage users login and register.
 * @param database The name of the database to connect to.
 * @param connection The name of the database connection to create.
 */
UserDB::UserDB(const QString& database, const QString& connection)
{
    db = QSqlDatabase::addDatabase("QMYSQL", connection);
    db.setHostName("<db_host>");
    db.setDatabaseName(database);
    db.setUserName("<db_user>");
    db.setPassword("<db_password>");
    if(!db.open())
        qDebug() << "Error: user database";
}

/**
 * @brief UserDB::~UserDB destroys the current instance of UserDB and closes the database connection.
 */
UserDB::~UserDB()
{
    db.close();
}

/**
 * @brief UserDB::userExists verifies if a user exists in the database.
 * @param username The username of the wanted user.
 * @param email The email address of the wanted user.
 * @return Returns true if the database contains the wanted user, false instead.
 */
bool UserDB::userExists(const QString& username, const QString& email) const
{
    Query query(db);
    query.prepare("SELECT * FROM ETUser WHERE username=:username OR email=:email;");
    query.bindValue(":username", username);
    query.bindValue(":email", email);
    query.execute();
    if(query.next())
        return true;
    return false;
}

/**
 * @brief UserDB::registerUser adds a user to the database.
 * @param username The username of the user to add.
 * @param password The password (hashed) of the user to add.
 * @param birth The birth date of the user to add.
 * @param email The email address of the user to add.
 * @param gender The gender of the user to add.
 * @return A boolean which indicates whether the adding was successful or not.
 */
bool UserDB::registerUser(const QString& username, const QString& password, const QDate& birth, const QString& email, const QString& gender) const
{
    Query query(db);
    query.prepare("INSERT INTO `ETUser`"
                  "(`username`, `password`, `birth`, `email`, `gender`, `budget`, `auth_attempt`) "
                  "VALUES (:username, :password, :birth, :email, :gender, :budget, 0);");
    query.bindValue(":username", username);
    query.bindValue(":password", password);
    query.bindValue(":birth", birth);
    query.bindValue(":email", email);
    query.bindValue(":budget", 2000);

    if (gender != "")
        query.bindValue(":gender", gender);
    else
        query.bindValue(":gender", QVariant(QString()));

    if(query.execute())
        return true;
    return false;
}

/**
 * @brief UserDB::loginUser gets the hashed password of a user.
 * @param username The username of the user whose hashed password we want to get.
 * @param password The variable in which the password will be stored.
 * @return A boolean which indicates whether the request was successful or not.
 */
bool UserDB::loginUser(const QString& username, QString& password) const
{
    Query query(db);
    query.prepare("SELECT password FROM ETUser WHERE username=:username;");
    query.bindValue(":username", username);
    query.execute();
    if(query.next()) {
        password = query.value(0).toString();
        return true;
    }
    return false;
}

/**
 * @brief UserDB::isAccountLocked checks if an account is locked.
 * @param username The username of the user to check.
 * @return True if the account is locked, false otherwise.
 */
bool UserDB::isAccountLocked(const QString& username)
{
    Query query(db);
    query.prepare("SELECT auth_attempt, last_auth_attempt FROM ETUser WHERE username = :username");
    query.bindValue(":username", username);
    if (query.exec() && query.next()) {
        int authAttempt = query.value(0).toInt();
        QDateTime lastAuthAttempt = query.value(1).toDateTime();
        QDateTime currentTime = QDateTime::currentDateTime();
        if (authAttempt >= 5 && lastAuthAttempt.addSecs(60*5) > currentTime)
            return true;
        else if (authAttempt >= 5 && lastAuthAttempt.addSecs(60*5) <= currentTime)
            resetAuthAttempts(username);
    }
    return false;
}

/**
 * @brief UserDB::incrementLoginAttempts increments the login attempts for a user.
 * @param username The username of the user to increment login attempts for.
 */
void UserDB::incrementLoginAttempts(const QString& username)
{
    Query query(db);
    query.prepare("SELECT auth_attempt FROM ETUser WHERE username = :username");
    query.bindValue(":username", username);
    if (query.exec() && query.next()) {
        int authAttempt = query.value(0).toInt();
        if (authAttempt == 4)
            query.prepare("UPDATE ETUser SET auth_attempt = 5, last_auth_attempt = CURRENT_TIMESTAMP WHERE username = :username");
        else
            query.prepare("UPDATE ETUser SET auth_attempt = auth_attempt + 1 WHERE username = :username");
        query.bindValue(":username", username);
        query.execute();
    }
}

/**
 * @brief UserDB::resetAuthAttempts resets the login attempts for a user.
 * @param username The username of the user to reset login attempts for.
 */
void UserDB::resetAuthAttempts(const QString& username)
{
    Query query(db);
    query.prepare("UPDATE ETUser SET auth_attempt = 0 WHERE username = :username");
    query.bindValue(":username", username);
    query.execute();
}

/**
 * @brief UserDB::getAuthAttempts gets the number of login attempts for a user.
 * @param username The username of the user to get login attempts for.
 * @return The number of login attempts.
 */
int UserDB::getAuthAttempts(const QString& username)
{
    Query query(db);
    query.prepare("SELECT auth_attempt FROM ETUser WHERE username = :username");
    query.bindValue(":username", username);
    if (query.exec() && query.next())
        return query.value(0).toInt();
    return 0;
}
