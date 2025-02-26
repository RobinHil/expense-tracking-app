#include "userdbtest.h"

#include "user.h"
#include "userdb.h"

UserDBTest::UserDBTest(QObject *parent)
    : QObject(parent),
      db("<db_name>", "test_userdb_setup_teardown_connection")
{}

// UserDB tests
void UserDBTest::test_userdb_registerUser()
{
    UserDB userdb("<db_name>", "test_registerUser_connection");
    QString testPassword = "testPassword123";
    User testUser("test user register", "test@test.test", QDate(2003, 6, 12), "m", 2000.32);
    QVERIFY(userdb.registerUser(testUser.getUsername(), testPassword, testUser.getBirth(), testUser.getEmail(), testUser.getGender()));
}

void UserDBTest::test_userdb_userExists_true()
{
    UserDB userdb("<db_name>", "test_userExists_true_connection");
    QString testPassword = "testPassword123";
    User testUser("test user exists true", "test@test.test", QDate(2003, 6, 12), "m", 2000.32);
    userdb.registerUser(testUser.getUsername(), testPassword, testUser.getBirth(), testUser.getEmail(), testUser.getGender());
    QVERIFY(userdb.userExists(testUser.getUsername(), testUser.getEmail()));
    QVERIFY(userdb.userExists(testUser.getUsername(), testUser.getUsername()));
    QVERIFY(userdb.userExists(testUser.getEmail(), testUser.getEmail()));
}

void UserDBTest::test_userdb_userExists_false()
{
    UserDB userdb("<db_name>", "test_userExists_false_connection");
    QString testPassword = "testPassword123";
    User testUser("test user exists false", "test@test.test", QDate(2003, 6, 12), "m", 2000.32);
    userdb.registerUser(testUser.getUsername(), testPassword, testUser.getBirth(), testUser.getEmail(), testUser.getGender());
    QVERIFY(!userdb.userExists("dkbzehfbehd", testUser.getUsername()));
    QVERIFY(!userdb.userExists(testUser.getEmail(), "lidnfnezounf"));
    QVERIFY(!userdb.userExists("hbejhfbezjhb", "ifbefbezifbez"));
}

void UserDBTest::test_userdb_loginUser()
{
    UserDB userdb("<db_name>", "test_loginUser_connection");
    QString testPassword = "testPassword123";
    User testUser("test user login", "test@test.test", QDate(2003, 6, 12), "m", 2000.32);
    userdb.registerUser(testUser.getUsername(), testPassword, testUser.getBirth(), testUser.getEmail(), testUser.getGender());
    QString dbPassword;
    QVERIFY(userdb.loginUser(testUser.getUsername(), dbPassword));
    QCOMPARE(dbPassword, testPassword);
}

void UserDBTest::test_userdb_loginUser_wrongPassword()
{
    UserDB userdb("<db_name>", "test_loginUser_wrongPassword_connection");
    QString testPassword = "testPassword123";
    User testUser("test user login wrong password", "test@test.test", QDate(2003, 6, 12), "m", 2000.32);
    userdb.registerUser(testUser.getUsername(), testPassword, testUser.getBirth(), testUser.getEmail(), testUser.getGender());
    QString dbPassword;
    QVERIFY(userdb.loginUser(testUser.getUsername(), dbPassword));
    QVERIFY(dbPassword != "wrongPassword456");
}

void UserDBTest::test_userdb_isAccountLocked_locked()
{
    UserDB userdb("<db_name>", "test_isAccountLocked_locked_connection");
    User testUser("test user account locked", "test@test.test", QDate(2003, 6, 12), "m", 2000.32);
    userdb.registerUser(testUser.getUsername(), "testPassword123", testUser.getBirth(), testUser.getEmail(), testUser.getGender());
    userdb.incrementLoginAttempts(testUser.getUsername());
    userdb.incrementLoginAttempts(testUser.getUsername());
    userdb.incrementLoginAttempts(testUser.getUsername());
    userdb.incrementLoginAttempts(testUser.getUsername());
    userdb.incrementLoginAttempts(testUser.getUsername());
    QVERIFY(userdb.isAccountLocked(testUser.getUsername()));
}

void UserDBTest::test_userdb_isAccountLocked_unlocked()
{
    UserDB userdb("<db_name>", "test_isAccountLocked_unlocked_connection");
    User testUser("test user account unlocked", "test@test.test", QDate(2003, 6, 12), "m", 2000.32);
    userdb.registerUser(testUser.getUsername(), "testPassword123", testUser.getBirth(), testUser.getEmail(), testUser.getGender());
    QVERIFY(!userdb.isAccountLocked(testUser.getUsername()));
}

void UserDBTest::test_userdb_incrementLoginAttempts()
{
    UserDB userdb("<db_name>", "test_incrementLoginAttempts_connection");
    User testUser("test user increment login attempts", "test@test.test", QDate(2003, 6, 12), "m", 2000.32);
    userdb.registerUser(testUser.getUsername(), "testPassword123", testUser.getBirth(), testUser.getEmail(), testUser.getGender());
    userdb.incrementLoginAttempts(testUser.getUsername());
    QCOMPARE(userdb.getAuthAttempts(testUser.getUsername()), 1);
    userdb.incrementLoginAttempts(testUser.getUsername());
    QCOMPARE(userdb.getAuthAttempts(testUser.getUsername()), 2);
    userdb.incrementLoginAttempts(testUser.getUsername());
    QCOMPARE(userdb.getAuthAttempts(testUser.getUsername()), 3);
    userdb.incrementLoginAttempts(testUser.getUsername());
    QCOMPARE(userdb.getAuthAttempts(testUser.getUsername()), 4);
    userdb.incrementLoginAttempts(testUser.getUsername());
    QCOMPARE(userdb.getAuthAttempts(testUser.getUsername()), 5);
}

void UserDBTest::test_userdb_resetAuthAttempts()
{
    UserDB userdb("<db_name>", "test_resetAuthAttempts_connection");
    User testUser("test user reset auth attempts", "test@test.test", QDate(2003, 6, 12), "m", 2000.32);
    userdb.registerUser(testUser.getUsername(), "testPassword123", testUser.getBirth(), testUser.getEmail(), testUser.getGender());
    userdb.incrementLoginAttempts(testUser.getUsername());
    userdb.incrementLoginAttempts(testUser.getUsername());
    userdb.incrementLoginAttempts(testUser.getUsername());
    QCOMPARE(userdb.getAuthAttempts(testUser.getUsername()), 3);
    userdb.resetAuthAttempts(testUser.getUsername());
    QCOMPARE(userdb.getAuthAttempts(testUser.getUsername()), 0);
}
