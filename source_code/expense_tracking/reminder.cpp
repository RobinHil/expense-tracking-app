#include "reminder.h"

/**
 * @brief Constructs a Reminder object without any parameters.
 */
Reminder::Reminder()
    : Reminder("", QDate(0,0,0))
{}

/**
 * @brief Constructs a Reminder object with all its member data.
 * @param _name The value of Reminder name member data.
 * @param _date The value of Reminder date member data.
 * @param _id The value of Reminder id member data.
 */
Reminder::Reminder(const QString& _name, const QDate& _date)
    : name(_name), date(_date)
{}

/**
 * @brief Destroys the current instance of Reminder.
 */
Reminder::~Reminder()
{}
