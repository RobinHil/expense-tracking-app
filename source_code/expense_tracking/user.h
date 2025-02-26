#ifndef USER_H
#define USER_H

#include <QString>
#include <QDate>

/**
 * @brief The User class represents a user with properties such as username, email, birth date, gender, and budget.
 */
class User{
    /** @brief Username. */
    QString username;

    /** @brief User email address. */
    QString email;

    /** @brief User birth date. */
    QDate birth;

    /** @brief User gender. */
    QString gender;

    /** @brief User budget. */
    double budget;

public:
    /**
     * @brief User Constructs a User object with default values.
     */
    User();

    /**
     * @brief User Constructs a User object with the given parameters.
     * @param username The username of the user.
     * @param email The email of the user.
     * @param birth The birth date of the user.
     * @param gender The gender of the user.
     * @param budget The budget of the user.
     */
    User(const QString&, const QString&, const QDate&, const QString&, const double&);

    /**
     * @brief ~User Destroys the User object.
     */
    ~User();

    /**
     * @brief getUsername Returns the username of the user.
     * @return The username of the user.
     */
    inline const QString& getUsername() const {return username;};

    /**
     * @brief setUsername Sets the username of the user.
     * @param _username The new username of the user.
     */
    inline void setUsername(const QString& _username) {username = _username;};

    /**
     * @brief getEmail Returns the email of the user.
     * @return The email of the user.
     */
    inline const QString& getEmail() const {return email;};

    /**
     * @brief setEmail Sets the email of the user.
     * @param _email The new email of the user.
     */
    inline void setEmail(const QString& _email) {email = _email;};

    /**
     * @brief getBirth Returns the birth date of the user.
     * @return The birth date of the user.
     */
    inline const QDate& getBirth() const {return birth;};

    /**
     * @brief setBirth Sets the birth date of the user.
     * @param _birth The new birth date of the user.
     */
    inline void setBirth(const QDate& _birth) {birth = _birth;};

    /**
     * @brief getGender Returns the gender of the user.
     * @return The gender of the user.
     */
    inline const QString& getGender() const {return gender;};

    /**
     * @brief setGender Sets the gender of the user.
     * @param _gender The new gender of the user.
     */
    inline void setGender(const QString& _gender) {gender = _gender;};

    /**
     * @brief getBudget Returns the budget of the user.
     * @return The budget of the user.
     */
    inline const double& getBudget() const {return budget;};

    /**
     * @brief setBudget Sets the budget of the user.
     * @param _budget The new budget of the user.
     */
    inline void setBudget(const double& _budget) {budget = _budget;};
};

#endif // USER_H
