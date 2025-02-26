#include "hashtest.h"
#include "hash.h"

HashTest::HashTest(QObject *parent)
    : QObject(parent)
{}

// Hash tests
void HashTest::test_hash_argon2id_nullPassword()
{
    QString hashHashTest = Hash::argon2id(QString());
    QVERIFY(hashHashTest.isNull());
}

void HashTest::test_hash_argon2id_nonNullPassword()
{
    QString testPassword = "testPassword123";
    QString hashHashTest = Hash::argon2id(testPassword);
    QVERIFY(!hashHashTest.isNull());
}

void HashTest::test_hash_verifyArgon2id_validPassword()
{
    QString testPassword = "testPassword123";
    QString hashHashTest = Hash::argon2id(testPassword);
    QVERIFY(Hash::verifyArgon2id(hashHashTest, testPassword));
}

void HashTest::test_hash_verifyArgon2id_invalidPassword()
{
    QString testPassword = "testPassword123";
    QString hashHashTest = Hash::argon2id(testPassword);
    QVERIFY(!Hash::verifyArgon2id(hashHashTest, "wrongPassword456"));
}

void HashTest::test_hash_verifyArgon2id_nullHash()
{
    QString testPassword = "testPassword123";
    QVERIFY(!Hash::verifyArgon2id(QString(), testPassword));
}

void HashTest::test_hash_verifyArgon2id_nullPassword()
{
    QString testPassword = "testPassword123";
    QString hashHashTest = Hash::argon2id(testPassword);
    QVERIFY(!Hash::verifyArgon2id(hashHashTest, QString()));
}
