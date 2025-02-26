#ifndef USERDB_H
#define USERDB_H

#include <QSqlDatabase>
#include <QDebug>
#include <QDate>

/**
 * @brief The UserDB class which manages the database requests to login and register users.
 */
class UserDB
{
    /**
     * @brief db The member data in which the database connection object will be stored.
     */
    QSqlDatabase db;

public:
    /**
     * @brief Constructs a new UserDB object.
     * @param username The database username.
     * @param password The database password.
     */
    UserDB(const QString&, const QString&);

    /**
     * @brief Destroys the UserDB object.
     */
    ~UserDB();

    /**
     * @brief Registers a new user.
     * @param name The user's name.
     * @param password The user's password.
     * @param birthDate The user's birth date.
     * @param email The user's email.
     * @param phone The user's phone number.
     * @return True if the user was registered successfully, false otherwise.
     */
    bool registerUser(const QString&, const QString&, const QDate&, const QString&, const QString& ="") const;

    /**
     * @brief Logs in a user.
     * @param name The user's name.
     * @param password The user's password.
     * @return True if the user was logged in successfully, false otherwise.
     */
    bool loginUser(const QString&, QString&) const;

    /**
     * @brief Checks if a user exists.
     * @param name The user's name.
     * @param password The user's password.
     * @return True if the user exists, false otherwise.
     */
    bool userExists(const QString&, const QString&) const;

    /**
     * @brief Increments the login attempts for a user.
     * @param name The user's name.
     */
    void incrementLoginAttempts(const QString&);

    /**
     * @brief Checks if a user's account is locked.
     * @param name The user's name.
     * @return True if the account is locked, false otherwise.
     */
    bool isAccountLocked(const QString&);

    /**
     * @brief Resets the authentication attempts for a user.
     * @param name The user's name.
     */
    void resetAuthAttempts(const QString&);

    /**
     * @brief Gets the number of authentication attempts for a user.
     * @param name The user's name.
     * @return The number of authentication attempts.
     */
    int getAuthAttempts(const QString&);
};

#endif // USERDB_H
