#ifndef HASH_H
#define HASH_H

#include <QString>
#include <sodium.h>

/**
 * @brief The Hash class in which we will manage the password hash.
 */
class Hash
{
    /**
     * @brief The pepper we will apply on all of the passwords before hash.
     */
    static const QString pepper;

public:
    Hash();

    static QString argon2id(const QString&);
    static bool verifyArgon2id(const QString&, const QString&);
};

#endif // HASH_H
