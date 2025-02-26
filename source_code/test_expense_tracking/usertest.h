#ifndef USERTEST_H
#define USERTEST_H

#include <QObject>
#include <QTest>

/**
 * @class UserTest
 * @brief The UserTest class is used for testing the User class.
 */
class UserTest : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief UserTest Constructs a UserTest object.
     * @param parent The parent object.
     */
    UserTest(QObject* parent = nullptr);

private slots:
    // Empty User tests

    /**
     * @brief test_user_empty_create Tests the creation of an empty User object.
     */
    void test_user_empty_create();

    /**
     * @brief test_user_empty_getUsername Tests the getUsername function of an empty User object.
     */
    void test_user_empty_getUsername();

    /**
     * @brief test_user_empty_getEmail Tests the getEmail function of an empty User object.
     */
    void test_user_empty_getEmail();

    /**
     * @brief test_user_empty_getBirth Tests the getBirth function of an empty User object.
     */
    void test_user_empty_getBirth();

    /**
     * @brief test_user_empty_getGender Tests the getGender function of an empty User object.
     */
    void test_user_empty_getGender();

    /**
     * @brief test_user_empty_getBudget Tests the getBudget function of an empty User object.
     */
    void test_user_empty_getBudget();

    /**
     * @brief test_user_empty_setUsername Tests the setUsername function of an empty User object.
     */
    void test_user_empty_setUsername();

    /**
     * @brief test_user_empty_setEmail Tests the setEmail function of an empty User object.
     */
    void test_user_empty_setEmail();

    /**
     * @brief test_user_empty_setBirth Tests the setBirth function of an empty User object.
     */
    void test_user_empty_setBirth();

    /**
     * @brief test_user_empty_setGender Tests the setGender function of an empty User object.
     */
    void test_user_empty_setGender();

    /**
     * @brief test_user_empty_setBudget Tests the setBudget function of an empty User object.
     */
    void test_user_empty_setBudget();

    // Filled User tests

    /**
     * @brief test_user_filled_create Tests the creation of a filled User object.
     */
    void test_user_filled_create();

    /**
     * @brief test_user_filled_getUsername Tests the getUsername function of a filled User object.
     */
    void test_user_filled_getUsername();

    /**
     * @brief test_user_filled_getEmail Tests the getEmail function of a filled User object.
     */
    void test_user_filled_getEmail();

    /**
     * @brief test_user_filled_getBirth Tests the getBirth function of a filled User object.
     */
    void test_user_filled_getBirth();

    /**
     * @brief test_user_filled_getGender Tests the getGender function of a filled User object.
     */
    void test_user_filled_getGender();

    /**
     * @brief test_user_filled_getBudget Tests the getBudget function of a filled User object.
     */
    void test_user_filled_getBudget();

    /**
     * @brief test_user_filled_setUsername Tests the setUsername function of a filled User object.
     */
    void test_user_filled_setUsername();

    /**
     * @brief test_user_filled_setEmail Tests the setEmail function of a filled User object.
     */
    void test_user_filled_setEmail();

    /**
     * @brief test_user_filled_setBirth Tests the setBirth function of a filled User object.
     */
    void test_user_filled_setBirth();

    /**
     * @brief test_user_filled_setGender Tests the setGender function of a filled User object.
     */
    void test_user_filled_setGender();

    /**
     * @brief test_user_filled_setBudget Tests the setBudget function of a filled User object.
     */
    void test_user_filled_setBudget();
};

#endif // USERTEST_H
