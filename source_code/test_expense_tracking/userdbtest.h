#ifndef USERDBTEST_H
#define USERDBTEST_H

#include <QObject>
#include <QTest>

#include "dbsetup.h"

/**
 * @class UserDBTest
 * @brief This class is used to test the UserDB class.
 */
class UserDBTest : public QObject
{
    Q_OBJECT

    dbSetup db; /**< An instance of the dbSetup class. */

public:
    /**
     * @brief Constructs a new UserDBTest object.
     * @param parent The parent object.
     */
    UserDBTest(QObject* =nullptr);

private slots:
    /**
     * @brief This function is called before the first test function is executed.
     * It initializes the database for testing.
     */
    void initTestCase() {
        if (!db.removeDatabase() || !db.createDatabase())
            QFAIL("Error while initializing the test database. End of tests.");
    }

    /**
     * @brief This function is called after the last test function is executed.
     * It cleans up the database.
     */
    void cleanupTestCase() {
        QVERIFY(db.removeDatabase());
    }

    // UserDB tests

    /**
     * @brief This function tests the registration of a new user.
     */
    void test_userdb_registerUser();

    /**
     * @brief This function tests if the user exists (true).
     */
    void test_userdb_userExists_true();

    /**
     * @brief This function tests if the user exists (false).
     */
    void test_userdb_userExists_false();

    /**
     * @brief This function tests the login of a user.
     */
    void test_userdb_loginUser();

    /**
     * @brief This function tests the login of a user with a wrong password.
     */
    void test_userdb_loginUser_wrongPassword();

    /**
     * @brief This function tests if the account is locked (locked).
     */
    void test_userdb_isAccountLocked_locked();

    /**
     * @brief This function tests if the account is locked (unlocked).
     */
    void test_userdb_isAccountLocked_unlocked();

    /**
     * @brief This function tests the increment of login attempts.
     */
    void test_userdb_incrementLoginAttempts();

    /**
     * @brief This function tests the reset of authentication attempts.
     */
    void test_userdb_resetAuthAttempts();
};

#endif // USERDBTEST_H
