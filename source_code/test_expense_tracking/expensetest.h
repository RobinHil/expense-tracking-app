#ifndef EXPENSETEST_H
#define EXPENSETEST_H

#include <QObject>
#include <QTest>

/**
 * @class ExpenseTest
 * @brief The ExpenseTest class provides testing functionalities for the Expense class.
 */
class ExpenseTest : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief ExpenseTest Constructs an ExpenseTest object with the given parent.
     * @param parent The parent object.
     */
    ExpenseTest(QObject* =nullptr);

private slots:
    // Empty Expense tests

    /**
     * @brief test_expense_empty_create Tests the creation of an empty Expense object.
     */
    void test_expense_empty_create();

    /**
     * @brief test_expense_empty_getName Tests the getName function of an empty Expense object.
     */
    void test_expense_empty_getName();

    /**
     * @brief test_expense_empty_getDescription Tests the getDescription function of an empty Expense object.
     */
    void test_expense_empty_getDescription();

    /**
     * @brief test_expense_empty_getCategory Tests the getCategory function of an empty Expense object.
     */
    void test_expense_empty_getCategory();

    /**
     * @brief test_expense_empty_getDate Tests the getDate function of an empty Expense object.
     */
    void test_expense_empty_getDate();

    /**
     * @brief test_expense_empty_getValue Tests the getValue function of an empty Expense object.
     */
    void test_expense_empty_getValue();

    /**
     * @brief test_expense_empty_setName Tests the setName function of an empty Expense object.
     */
    void test_expense_empty_setName();

    /**
     * @brief test_expense_empty_setDescription Tests the setDescription function of an empty Expense object.
     */
    void test_expense_empty_setDescription();

    /**
     * @brief test_expense_empty_setCategory Tests the setCategory function of an empty Expense object.
     */
    void test_expense_empty_setCategory();

    /**
     * @brief test_expense_empty_setDate Tests the setDate function of an empty Expense object.
     */
    void test_expense_empty_setDate();

    /**
     * @brief test_expense_empty_setValue Tests the setValue function of an empty Expense object.
     */
    void test_expense_empty_setValue();

    // Filled Expense tests

    /**
     * @brief test_expense_filled_create Tests the creation of a filled Expense object.
     */
    void test_expense_filled_create();

    /**
     * @brief test_expense_filled_getName Tests the getName function of a filled Expense object.
     */
    void test_expense_filled_getName();

    /**
     * @brief test_expense_filled_getDescription Tests the getDescription function of a filled Expense object.
     */
    void test_expense_filled_getDescription();

    /**
     * @brief test_expense_filled_getCategory Tests the getCategory function of a filled Expense object.
     */
    void test_expense_filled_getCategory();

    /**
     * @brief test_expense_filled_getDate Tests the getDate function of a filled Expense object.
     */
    void test_expense_filled_getDate();

    /**
     * @brief test_expense_filled_getValue Tests the getValue function of a filled Expense object.
     */
    void test_expense_filled_getValue();

    /**
     * @brief test_expense_filled_setName Tests the setName function of a filled Expense object.
     */
    void test_expense_filled_setName();

    /**
     * @brief test_expense_filled_setDescription Tests the setDescription function of a filled Expense object.
     */
    void test_expense_filled_setDescription();

    /**
     * @brief test_expense_filled_setCategory Tests the setCategory function of a filled Expense object.
     */
    void test_expense_filled_setCategory();

    /**
     * @brief test_expense_filled_setDate Tests the setDate function of a filled Expense object.
     */
    void test_expense_filled_setDate();

    /**
     * @brief test_expense_filled_setValue Tests the setValue function of a filled Expense object.
     */
    void test_expense_filled_setValue();
};

#endif // EXPENSETEST_H
