#ifndef REMINDERTEST_H
#define REMINDERTEST_H

#include <QObject>
#include <QTest>

/**
 * @class ReminderTest
 * @brief This class is used to test the Reminder class.
 */
class ReminderTest : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief Constructs a new ReminderTest object.
     * @param parent The parent object.
     */
    ReminderTest(QObject* parent = nullptr);

private slots:
    // Empty Reminder tests

    /**
     * @brief This function tests the creation of an empty Reminder object.
     */
    void test_reminder_empty_create();

    /**
     * @brief This function tests the getName function of an empty Reminder object.
     */
    void test_reminder_empty_getName();

    /**
     * @brief This function tests the getDate function of an empty Reminder object.
     */
    void test_reminder_empty_getDate();

    /**
     * @brief This function tests the setName function of an empty Reminder object.
     */
    void test_reminder_empty_setName();

    /**
     * @brief This function tests the setDate function of an empty Reminder object.
     */
    void test_reminder_empty_setDate();

    // Filled Reminder tests

    /**
     * @brief This function tests the creation of a filled Reminder object.
     */
    void test_reminder_filled_create();

    /**
     * @brief This function tests the getName function of a filled Reminder object.
     */
    void test_reminder_filled_getName();

    /**
     * @brief This function tests the getDate function of a filled Reminder object.
     */
    void test_reminder_filled_getDate();

    /**
     * @brief This function tests the setName function of a filled Reminder object.
     */
    void test_reminder_filled_setName();

    /**
     * @brief This function tests the setDate function of a filled Reminder object.
     */
    void test_reminder_filled_setDate();
};

#endif // REMINDERTEST_H
