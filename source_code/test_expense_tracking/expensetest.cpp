#include "expensetest.h"
#include "expense.h"

ExpenseTest::ExpenseTest(QObject *parent)
    : QObject(parent)
{}

// Empty Expense tests
void ExpenseTest::test_expense_empty_create()
{
    Expense expense;
    QCOMPARE(expense.getName(), QString());
    QCOMPARE(expense.getDescription(), QString());
    QCOMPARE(expense.getCategory(), 0);
    QCOMPARE(expense.getDate(), QDate());
    QCOMPARE(expense.getValue(), 0.0);
}

void ExpenseTest::test_expense_empty_getName()
{
    Expense expense;
    QCOMPARE(expense.getName(), QString());
}

void ExpenseTest::test_expense_empty_getDescription()
{
    Expense expense;
    QCOMPARE(expense.getDescription(), QString());
}

void ExpenseTest::test_expense_empty_getCategory()
{
    Expense expense;
    QCOMPARE(expense.getCategory(), 0);
}

void ExpenseTest::test_expense_empty_getDate()
{
    Expense expense;
    QCOMPARE(expense.getDate(), QDate());
}

void ExpenseTest::test_expense_empty_getValue()
{
    Expense expense;
    QCOMPARE(expense.getValue(), 0.0);
}

void ExpenseTest::test_expense_empty_setName()
{
    Expense expense;
    expense.setName("test expense 1");
    QCOMPARE(expense.getName(), QString("test expense 1"));
    QCOMPARE(expense.getDescription(), QString());
    QCOMPARE(expense.getCategory(), 0);
    QCOMPARE(expense.getDate(), QDate());
    QCOMPARE(expense.getValue(), 0.0);
}

void ExpenseTest::test_expense_empty_setDescription()
{
    Expense expense;
    expense.setDescription("test expense description 1");
    QCOMPARE(expense.getName(), QString());
    QCOMPARE(expense.getDescription(), QString("test expense description 1"));
    QCOMPARE(expense.getCategory(), 0);
    QCOMPARE(expense.getDate(), QDate());
    QCOMPARE(expense.getValue(), 0.0);
}

void ExpenseTest::test_expense_empty_setCategory()
{
    Expense expense;
    expense.setCategory(12);
    QCOMPARE(expense.getName(), QString());
    QCOMPARE(expense.getDescription(), QString());
    QCOMPARE(expense.getCategory(), 12);
    QCOMPARE(expense.getDate(), QDate());
    QCOMPARE(expense.getValue(), 0.0);
}

void ExpenseTest::test_expense_empty_setDate()
{
    Expense expense;
    expense.setDate(QDate(2003, 12, 3));
    QCOMPARE(expense.getName(), QString());
    QCOMPARE(expense.getDescription(), QString());
    QCOMPARE(expense.getCategory(), 0);
    QCOMPARE(expense.getDate(), QDate(2003, 12, 3));
    QCOMPARE(expense.getValue(), 0.0);
}

void ExpenseTest::test_expense_empty_setValue()
{
    Expense expense;
    expense.setValue(92381.2392);
    QCOMPARE(expense.getName(), QString());
    QCOMPARE(expense.getDescription(), QString());
    QCOMPARE(expense.getCategory(), 0);
    QCOMPARE(expense.getDate(), QDate());
    QCOMPARE(expense.getValue(), 92381.2392);
}

// Filled Expense tests
void ExpenseTest::test_expense_filled_create()
{
    Expense expense("test expense", "test expense description", 4, QDate(2021, 10, 17), 1028283.29382);
    QCOMPARE(expense.getName(), QString("test expense"));
    QCOMPARE(expense.getDescription(), QString("test expense description"));
    QCOMPARE(expense.getCategory(), 4);
    QCOMPARE(expense.getDate(), QDate(2021, 10, 17));
    QCOMPARE(expense.getValue(), 1028283.29382);
}

void ExpenseTest::test_expense_filled_getName()
{
    Expense expense("test expense", "test expense description", 4, QDate(2021, 10, 17), 1028283.29382);
    QCOMPARE(expense.getName(), QString("test expense"));
}

void ExpenseTest::test_expense_filled_getDescription()
{
    Expense expense("test expense", "test expense description", 4, QDate(2021, 10, 17), 1028283.29382);
    QCOMPARE(expense.getDescription(), QString("test expense description"));
}

void ExpenseTest::test_expense_filled_getCategory()
{
    Expense expense("test expense", "test expense description", 4, QDate(2021, 10, 17), 1028283.29382);
    QCOMPARE(expense.getCategory(), 4);
}

void ExpenseTest::test_expense_filled_getDate()
{
    Expense expense("test expense", "test expense description", 4, QDate(2021, 10, 17), 1028283.29382);
    QCOMPARE(expense.getDate(), QDate(2021, 10, 17));
}

void ExpenseTest::test_expense_filled_getValue()
{
    Expense expense("test expense", "test expense description", 4, QDate(2021, 10, 17), 1028283.29382);
    QCOMPARE(expense.getValue(), 1028283.29382);
}

void ExpenseTest::test_expense_filled_setName()
{
    Expense expense("test expense", "test expense description", 4, QDate(2021, 10, 17), 1028283.29382);
    expense.setName("test expense 2");
    QCOMPARE(expense.getName(), QString("test expense 2"));
    QCOMPARE(expense.getDescription(), QString("test expense description"));
    QCOMPARE(expense.getCategory(), 4);
    QCOMPARE(expense.getDate(), QDate(2021, 10, 17));
    QCOMPARE(expense.getValue(), 1028283.29382);
}

void ExpenseTest::test_expense_filled_setDescription()
{
    Expense expense("test expense", "test expense description", 4, QDate(2021, 10, 17), 1028283.29382);
    expense.setDescription("test expense description 2");
    QCOMPARE(expense.getName(), QString("test expense"));
    QCOMPARE(expense.getDescription(), QString("test expense description 2"));
    QCOMPARE(expense.getCategory(), 4);
    QCOMPARE(expense.getDate(), QDate(2021, 10, 17));
    QCOMPARE(expense.getValue(), 1028283.29382);
}

void ExpenseTest::test_expense_filled_setCategory()
{
    Expense expense("test expense", "test expense description", 4, QDate(2021, 10, 17), 1028283.29382);
    expense.setCategory(1003);
    QCOMPARE(expense.getName(), QString("test expense"));
    QCOMPARE(expense.getDescription(), QString("test expense description"));
    QCOMPARE(expense.getCategory(), 1003);
    QCOMPARE(expense.getDate(), QDate(2021, 10, 17));
    QCOMPARE(expense.getValue(), 1028283.29382);
}

void ExpenseTest::test_expense_filled_setDate()
{
    Expense expense("test expense", "test expense description", 4, QDate(2021, 10, 17), 1028283.29382);
    expense.setDate(QDate(2009, 10, 27));
    QCOMPARE(expense.getName(), QString("test expense"));
    QCOMPARE(expense.getDescription(), QString("test expense description"));
    QCOMPARE(expense.getCategory(), 4);
    QCOMPARE(expense.getDate(), QDate(2009, 10, 27));
    QCOMPARE(expense.getValue(), 1028283.29382);
}

void ExpenseTest::test_expense_filled_setValue()
{
    Expense expense("test expense", "test expense description", 4, QDate(2021, 10, 17), 1028283.29382);
    expense.setValue(4472873.4728);
    QCOMPARE(expense.getName(), QString("test expense"));
    QCOMPARE(expense.getDescription(), QString("test expense description"));
    QCOMPARE(expense.getCategory(), 4);
    QCOMPARE(expense.getDate(), QDate(2021, 10, 17));
    QCOMPARE(expense.getValue(), 4472873.4728);
}
