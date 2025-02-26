#ifndef EXPENSETRACKING_H
#define EXPENSETRACKING_H

#include <QMap>
#include <QSql>
#include <QSqlDatabase>
#include <QTextStream>
#include <QString>

#include "category.h"
#include "expense.h"
#include "reminder.h"
#include "user.h"

/**
 * @brief The ExpenseTracking class manages the tracking and operations related to expenses.
 */
class ExpenseTracking
{
    /**
     * @brief Helper function to add a line to a CSV file.
     * @param stream Reference to QTextStream for writing to the CSV file.
     * @param strList List of strings representing the data to be written.
     */
    void addLineToCSV(QTextStream&, const QStringList&) const;

    /**
     * @brief username The username of the currently logged user.
     */
    QString username;

    /**
     * @brief db The member data in which the database connection object will be stored.
     */
    QSqlDatabase db;

public:
    /**
     * @brief Constructor for ExpenseTracking.
     * @param file The database file name. Defaults to "ExpenseTracking.db".
     */
    ExpenseTracking(const QString&, const QString&, const QString&);

    /// @brief Destructor for ExpenseTracking.
    ~ExpenseTracking();

    // Category-related methods
    /**
     * @brief Adds a category to the application.
     * @param category The Category object to add.
     */
    void addCategory(const Category&) const;

    /**
     * @brief Removes a category based on its ID.
     * @param id The ID of the category to remove.
     */
    void removeCategory(const unsigned int&) const;

    /**
     * @brief Updates the information of an existing category.
     * @param id The ID of the category to update.
     * @param category The updated Category object.
     */
    void updateCategory(const unsigned int&, const Category&) const;

    /**
     * @brief Retrieves a specific category by its ID.
     * @param id The ID of the category to retrieve.
     * @return The retrieved Category object.
     */
    Category getCategory(const int&) const;

    /**
     * @brief Retrieves a map of all categories in the application.
     * @return A QMap containing all categories.
     */
    QMap<int,Category> getCategories() const;

    // Expense-related methods
    /**
     * @brief Adds an expense to the application.
     * @param expense The Expense object to add.
     */
    void addExpense(const Expense&) const;

    /**
     * @brief Removes an expense based on its ID.
     * @param id The ID of the expense to remove.
     */
    void removeExpense(const unsigned int&) const;

    /**
     * @brief Updates the information of an existing expense.
     * @param id The ID of the expense to update.
     * @param expense The updated Expense object.
     */
    void updateExpense(const unsigned int&, const Expense&) const;

    Expense getExpense(const int&) const;

    /**
     * @brief Retrieves a vector of expenses based on various criteria.
     * @param category The category ID for filtering (default: 0 for no filter).
     * @param searchQuery The search query for filtering (default: "" for no filter).
     * @param criterion Additional criteria (default: 0 for no filter).
     * @param date The date for filtering (default: QDate(0,0,0) for no filter).
     * @return A QVector of expense pairs (ID and Expense object).
     */
    QVector<QPair<int,Expense>> getExpenses(const int& =0, const QString& ="", const int& =0, const QDate& =QDate(0,0,0)) const;

    /**
     * @brief Retrieves expenses without a search query.
     * @param category The category ID for filtering (default: 0 for no filter).
     * @param criterion Additional criteria (default: 0 for no filter).
     * @param date The date for filtering (default: QDate(0,0,0) for no filter).
     * @return A QVector of expense pairs (ID and Expense object).
     */
    QVector<QPair<int,Expense>> getExpWithoutSearch(const int& =0, const int& =0, const QDate& =QDate(0,0,0)) const;

    /**
     * @brief Retrieves expenses sum for a given date.
     * @param criterion Additional criteria (default: 0 for no filter).
     * @param date The date for filtering (default: QDate(0,0,0) for no filter).
     * @return A double value that's the sum of expenses for the selected period.
     */
    double getExpensesSum(const int& =0, const QDate& =QDate(0,0,0)) const;

    // Reminder-related methods

    /**
     * @brief Adds a reminder to the application.
     * @param reminder The Reminder object to add.
     */
    void addReminder(const Reminder&) const;

    /**
     * @brief Updates the information of an existing reminder.
     * @param id The ID of the reminder to update.
     * @param reminder The updated Reminder object.
     */
    void updateReminder(const unsigned int&, const Reminder&) const;

    /**
     * @brief Retrieves the current budget value.
     * @return The current budget as a double.
     */
    double getBudget() const;

    /**
     * @brief Updates the budget value.
     * @param newbudget The new budget value.
     */
    void updateBudget(const double&) const;

    /**
     * @brief Removes a reminder based on its ID.
     * @param id The ID of the reminder to remove.
     */
    void removeReminder(const unsigned int&) const;

    /**
     * @brief Retrieves a map of reminders, optionally including only expired ones.
     * @param expired Indicates whether to include only expired reminders (default: false).
     * @return A QMap containing reminders.
     */
    QMap<int, Reminder> getReminders(const bool& =false) const;

    /**
     * @brief updateUser modifies user's data.
     * @param email The new user's email address.
     * @param birth The new user's birth date.
     * @param gender The new user's gender.
     */
    void updateUser(const QString&, const QDate&, const QString&) const;

    /**
     * @brief removeUser removes the user.
     */
    void removeUser() const;

    /**
     * @brief getUser gets the user's information.
     */
    User getUser() const;

    /**
     * @brief Exports data to a CSV file.
     * @param file The file name for the CSV export.
     */
    void exportToCSV(const QString&) const;

    bool getUserPassword(QString&) const;
    bool updatePassword(const QString&) const;
};

#endif // EXPENSETRACKING_H
