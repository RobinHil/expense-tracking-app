#ifndef HASHTEST_H
#define HASHTEST_H

#include <QObject>
#include <QTest>

/**
 * @class HashTest
 * @brief The HashTest class provides testing functionalities for the hash functions.
 *
 * This class is used to test the functionality and correctness of the hash functions.
 */
class HashTest : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief HashTest Constructs a new HashTest object.
     * @param parent The parent object.
     */
    HashTest(QObject* =nullptr);

private slots:
    /**
     * @brief test_hash_argon2id_nullPassword This function tests the hash function with a null password.
     */
    void test_hash_argon2id_nullPassword();

    /**
     * @brief test_hash_argon2id_nonNullPassword This function tests the hash function with a non-null password.
     */
    void test_hash_argon2id_nonNullPassword();

    /**
     * @brief test_hash_verifyArgon2id_validPassword This function tests the verifyArgon2id function with a valid password.
     */
    void test_hash_verifyArgon2id_validPassword();

    /**
     * @brief test_hash_verifyArgon2id_invalidPassword This function tests the verifyArgon2id function with an invalid password.
     */
    void test_hash_verifyArgon2id_invalidPassword();

    /**
     * @brief test_hash_verifyArgon2id_nullHash This function tests the verifyArgon2id function with a null hash.
     */
    void test_hash_verifyArgon2id_nullHash();

    /**
     * @brief test_hash_verifyArgon2id_nullPassword This function tests the verifyArgon2id function with a null password.
     */
    void test_hash_verifyArgon2id_nullPassword();
};

#endif // HASHTEST_H
