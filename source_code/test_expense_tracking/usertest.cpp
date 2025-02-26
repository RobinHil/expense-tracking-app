#include "usertest.h"
#include "user.h"

UserTest::UserTest(QObject *parent)
    : QObject(parent)
{}

// Empty User tests
void UserTest::test_user_empty_create()
{
    User user;
    QCOMPARE(user.getUsername(), QString());
    QCOMPARE(user.getEmail(), QString());
    QCOMPARE(user.getBirth(), QDate(0,0,0));
    QCOMPARE(user.getGender(), QString());
    QCOMPARE(user.getBudget(), 0.0);
}

void UserTest::test_user_empty_getUsername()
{
    User user;
    QCOMPARE(user.getUsername(), QString());
}

void UserTest::test_user_empty_getEmail()
{
    User user;
    QCOMPARE(user.getEmail(), QString());
}

void UserTest::test_user_empty_getBirth()
{
    User user;
    QCOMPARE(user.getBirth(), QDate(0,0,0));
}

void UserTest::test_user_empty_getGender()
{
    User user;
    QCOMPARE(user.getGender(), QString());
}

void UserTest::test_user_empty_getBudget()
{
    User user;
    QCOMPARE(user.getBudget(), 0.0);
}

void UserTest::test_user_empty_setUsername()
{
    User user;
    user.setUsername("test user 1");
    QCOMPARE(user.getUsername(), QString("test user 1"));
    QCOMPARE(user.getEmail(), QString());
    QCOMPARE(user.getBirth(), QDate(0,0,0));
    QCOMPARE(user.getGender(), QString());
    QCOMPARE(user.getBudget(), 0.0);
}

void UserTest::test_user_empty_setEmail()
{
    User user;
    user.setEmail("test1@test1.test1");
    QCOMPARE(user.getUsername(), QString());
    QCOMPARE(user.getEmail(), QString("test1@test1.test1"));
    QCOMPARE(user.getBirth(), QDate(0,0,0));
    QCOMPARE(user.getGender(), QString());
    QCOMPARE(user.getBudget(), 0.0);
}

void UserTest::test_user_empty_setBirth()
{
    User user;
    user.setBirth(QDate(2002, 11, 30));
    QCOMPARE(user.getUsername(), QString());
    QCOMPARE(user.getEmail(), QString());
    QCOMPARE(user.getBirth(), QDate(2002, 11, 30));
    QCOMPARE(user.getGender(), QString());
    QCOMPARE(user.getBudget(), 0.0);
}

void UserTest::test_user_empty_setGender()
{
    User user;
    user.setGender("f");
    QCOMPARE(user.getUsername(), QString());
    QCOMPARE(user.getEmail(), QString());
    QCOMPARE(user.getBirth(), QDate(0,0,0));
    QCOMPARE(user.getGender(), QString("f"));
    QCOMPARE(user.getBudget(), 0.0);
}

void UserTest::test_user_empty_setBudget()
{
    User user;
    user.setBudget(2938329.2939);
    QCOMPARE(user.getUsername(), QString());
    QCOMPARE(user.getEmail(), QString());
    QCOMPARE(user.getBirth(), QDate(0,0,0));
    QCOMPARE(user.getGender(), QString());
    QCOMPARE(user.getBudget(), 2938329.2939);
}

// Filled User tests
void UserTest::test_user_filled_create()
{
    User user("test user", "test@test.test", QDate(2004, 4, 3), "m", 2000.32);
    QCOMPARE(user.getUsername(), QString("test user"));
    QCOMPARE(user.getEmail(), QString("test@test.test"));
    QCOMPARE(user.getBirth(), QDate(2004, 4, 3));
    QCOMPARE(user.getGender(), QString("m"));
    QCOMPARE(user.getBudget(), 2000.32);
}

void UserTest::test_user_filled_getUsername()
{
    User user("test user", "test@test.test", QDate(2004, 4, 3), "m", 2000.32);
    QCOMPARE(user.getUsername(), QString("test user"));
}

void UserTest::test_user_filled_getEmail()
{
    User user("test user", "test@test.test", QDate(2004, 4, 3), "m", 2000.32);
    QCOMPARE(user.getEmail(), QString("test@test.test"));
}

void UserTest::test_user_filled_getBirth()
{
    User user("test user", "test@test.test", QDate(2004, 4, 3), "m", 2000.32);
    QCOMPARE(user.getBirth(), QDate(2004, 4, 3));
}

void UserTest::test_user_filled_getGender()
{
    User user("test user", "test@test.test", QDate(2004, 4, 3), "m", 2000.32);
    QCOMPARE(user.getGender(), QString("m"));
}

void UserTest::test_user_filled_getBudget()
{
    User user("test user", "test@test.test", QDate(2004, 4, 3), "m", 2000.32);
    QCOMPARE(user.getBudget(), 2000.32);
}

void UserTest::test_user_filled_setBudget()
{
    User user("test user", "test@test.test", QDate(2004, 4, 3), "m", 2000.32);
    user.setBudget(283.293);
    QCOMPARE(user.getUsername(), QString("test user"));
    QCOMPARE(user.getEmail(), QString("test@test.test"));
    QCOMPARE(user.getBirth(), QDate(2004, 4, 3));
    QCOMPARE(user.getGender(), QString("m"));
    QCOMPARE(user.getBudget(), 283.293);
}

void UserTest::test_user_filled_setGender()
{
    User user("test user", "test@test.test", QDate(2004, 4, 3), "m", 2000.32);
    user.setGender("");
    QCOMPARE(user.getUsername(), QString("test user"));
    QCOMPARE(user.getEmail(), QString("test@test.test"));
    QCOMPARE(user.getBirth(), QDate(2004, 4, 3));
    QCOMPARE(user.getGender(), QString());
    QCOMPARE(user.getBudget(), 2000.32);
}

void UserTest::test_user_filled_setBirth()
{
    User user("test user", "test@test.test", QDate(2004, 4, 3), "m", 2000.32);
    user.setBirth(QDate(2003, 6, 12));
    QCOMPARE(user.getUsername(), QString("test user"));
    QCOMPARE(user.getEmail(), QString("test@test.test"));
    QCOMPARE(user.getBirth(), QDate(2003, 6, 12));
    QCOMPARE(user.getGender(), QString("m"));
    QCOMPARE(user.getBudget(), 2000.32);
}

void UserTest::test_user_filled_setEmail()
{
    User user("test user", "test@test.test", QDate(2004, 4, 3), "m", 2000.32);
    user.setEmail("test2@test2.test2");
    QCOMPARE(user.getUsername(), QString("test user"));
    QCOMPARE(user.getEmail(), QString("test2@test2.test2"));
    QCOMPARE(user.getBirth(), QDate(2004, 4, 3));
    QCOMPARE(user.getGender(), QString("m"));
    QCOMPARE(user.getBudget(), 2000.32);
}

void UserTest::test_user_filled_setUsername()
{
    User user("test user", "test@test.test", QDate(2004, 4, 3), "m", 2000.32);
    user.setUsername("test user 2");
    QCOMPARE(user.getUsername(), QString("test user 2"));
    QCOMPARE(user.getEmail(), QString("test@test.test"));
    QCOMPARE(user.getBirth(), QDate(2004, 4, 3));
    QCOMPARE(user.getGender(), QString("m"));
    QCOMPARE(user.getBudget(), 2000.32);
}
