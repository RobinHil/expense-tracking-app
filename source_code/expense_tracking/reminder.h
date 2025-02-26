#ifndef REMINDER_H
#define REMINDER_H

#include <QString>
#include <QDate>

/**
 * @brief The Reminder class represents a reminder with a name and a date.
 */
class Reminder
{
    QString name; /**< The name of the reminder. */
    QDate date; /**< The date of the reminder. */

public:
    /**
     * @brief Default constructor for the Reminder class.
     */
    Reminder();
    /**
     * @brief Constructor for the Reminder class with name and date parameters.
     * @param name The name of the reminder.
     * @param date The date of the reminder.
     */
    Reminder(const QString&, const QDate&);
    /**
     * @brief Destructor for the Reminder class.
     */
    ~Reminder();

    /**
     * @brief A simple getter for the name.
     * @return The current instance name.
     */
    inline const QString& getName() const {return name;};

    /**
     * @brief A simple setter for the name.
     * @param _name New name value.
     */
    inline void setName(const QString& _name) {name = _name;};

    /**
     * @brief A simple getter for the date.
     * @return The current instance date.
     */
    inline const QDate& getDate() const {return date;};

    /**
     * @brief A simple setter for the date.
     * @param _date New date value.
     */
    inline void setDate(const QDate& _date) {date = _date;};
};

#endif // REMINDER_H
