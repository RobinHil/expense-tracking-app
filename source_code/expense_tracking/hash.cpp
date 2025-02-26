#include "hash.h"

const QString Hash::pepper="c0m3UcE4WDthSDdyY4bCPbZmptXdEJ2Y";

/**
 * @brief Hash::Hash creates an instance of Hash class.
 */
Hash::Hash() {}

/**
 * @brief Hash::argon2id applies a hash with argon2id algorithm to the entered string.
 * @param toHash The string to hash.
 * @return The hash result.
 */
QString Hash::argon2id(const QString& toHash)
{
    if (toHash.isEmpty())
        return NULL;

    const size_t HASH_SIZE = crypto_pwhash_argon2id_STRBYTES;
    const size_t OPSLIMIT = 10;
    const size_t MEMLIMIT = crypto_pwhash_argon2id_MEMLIMIT_INTERACTIVE;

    QString pepperyToHash = toHash+pepper;

    char hashed[HASH_SIZE];
    if (
        crypto_pwhash_argon2id_str(
            hashed,
            pepperyToHash.toUtf8().constData(),
            pepperyToHash.length(),
            OPSLIMIT,
            MEMLIMIT
        ) == 0
    ) return QString::fromUtf8(hashed);

    return NULL;
}

/**
 * @brief Hash::verifyArgon2id checks if a character string corresponds to a hash.
 * @param hash The hash to check.
 * @param toVerify The string to check.
 * @return Returns true if the string to verify matches the hash, false otherwise
 */
bool Hash::verifyArgon2id(const QString& hash, const QString& toVerify)
{
    QString pepperyToVerify = toVerify+pepper;

    if (
        crypto_pwhash_str_verify(
            hash.toUtf8().constData(),
            pepperyToVerify.toUtf8().constData(),
            pepperyToVerify.length()
        ) == 0
    ) return true;

    return false;
}
