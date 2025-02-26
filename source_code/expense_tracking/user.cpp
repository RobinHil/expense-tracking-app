#include "user.h"

/** @brief Creates an instance of User without any parameters. */
User::User()
    : User("","",QDate(0,0,0),"",0)
{}

/**
 * @brief User::User creates an instance of User with all parameters.
 * @param _username The username.
 * @param _email The user email.
 * @param _birth The user birth date.
 * @param _gender The user gender.
 * @param _budget The user budget.
 */
User::User(const QString& _username, const QString& _email, const QDate& _birth, const QString& _gender, const double& _budget)
    : username(_username), email(_email), birth(_birth), gender(_gender), budget(_budget)
{}

/** @brief Destroys the current instance of User. */
User::~User()
{}
