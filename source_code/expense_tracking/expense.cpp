#include "expense.h"

/**
 * @brief Creates an instance of Expense without any parameters.
 */
Expense::Expense()
    : Expense("", "", 0, QDate(0,0,0), 0)
{}

/**
 * @brief Creates an instance of Expense with all its member data.
 * @param _name The value of Expense name member data.
 * @param _description The value of Expense description member data.
 * @param _category A pointer on the category of Expense.
 * @param _date The value of Expense date member data.
 * @param _value The value of Expense value member data.
 * @param _id The value of Expense id member data.
 */
Expense::Expense(const QString& _name, const QString& _description, const int& _category, const QDate& _date, const double& _value)
    : name(_name), description(_description), date(_date), value(_value), category(_category)
{}

/**
 * @brief Destroys the current instance of Expense.
 */
Expense::~Expense()
{}

/**
 * @brief Checks if two Expense objects are equal.
 * @param other The Expense object to compare with the current object.
 * @return true if the objects are equal, false otherwise.
 */
bool Expense::operator==(const Expense& other) const
{
    return (name == other.name &&
            description == other.description &&
            category == other.category &&
            date == other.date &&
            value == other.value);
}
