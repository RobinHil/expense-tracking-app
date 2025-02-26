#ifndef EXPENSE_H
#define EXPENSE_H

#include <QString>
#include <QDate>

class Expense{
    /** @brief Expense name. */
    QString name;

    /** @brief Expense description. */
    QString description;

    /** @brief Expense date. */
    QDate date;

    /** @brief Expense value. */
    double value;

    /** @brief Expense Category. */
    int category;

public:
    /**
     * @brief Default constructor.
     */
    Expense();

    /**
     * @brief Parameterized constructor.
     * @param name The name of the expense.
     * @param description The description of the expense.
     * @param category The category of the expense.
     * @param date The date of the expense.
     * @param value The value of the expense.
     */
    Expense(const QString&, const QString&, const int&, const QDate&, const double&);

    /**
     * @brief Destructor.
     */
    ~Expense();

    /**
     * @brief A simple getter.
     * @return Current instance name.
     */
    inline const QString& getName() const {return name;};

    /**
     * @brief A simple setter.
     * @param _name New name value.
     */
    inline void setName(const QString& _name) {name = _name;};

    /**
     * @brief A simple getter.
     * @return Current instance description.
     */
    inline const QString& getDescription() const {return description;};

    /**
     * @brief A simple setter.
     * @param _description New description value.
     */
    inline void setDescription(const QString& _description) {description = _description;};

    /**
     * @brief A simple getter.
     * @return Current instance date.
     */
    inline const QDate& getDate() const {return date;};

    /**
     * @brief A simple setter.
     * @param _date New date value.
     */
    inline void setDate(const QDate& _date) {date = _date;};

    /**
     * @brief A simple getter.
     * @return Current instance value.
     */
    inline const double& getValue() const {return value;};

    /**
     * @brief A simple setter.
     * @param _value New value.
     */
    inline void setValue(const double& _value) {value = _value;};

    /**
     * @brief A simple getter.
     * @return Current category id.
     */
    inline int getCategory() const {return category;};

    /**
     * @brief A simple setter.
     * @param _category New Category id.
     */
    inline void setCategory(const int& _category) {category = _category;};

    /**
     * @brief Checks if two Expense objects are equal.
     * @param other The Expense object to compare with the current object.
     * @return true if the objects are equal, false otherwise.
     */
    bool operator==(const Expense&) const;
};

#endif // EXPENSE_H
