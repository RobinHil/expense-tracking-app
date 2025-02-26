#include "remindertest.h"
#include "reminder.h"

ReminderTest::ReminderTest(QObject *parent)
    : QObject(parent)
{}

// Empty Reminder tests
void ReminderTest::test_reminder_empty_create()
{
    Reminder reminder;
    QCOMPARE(reminder.getName(), QString());
    QCOMPARE(reminder.getDate(), QDate());
}

void ReminderTest::test_reminder_empty_getName()
{
    Reminder reminder;
    QCOMPARE(reminder.getName(), QString());
}

void ReminderTest::test_reminder_empty_getDate()
{
    Reminder reminder;
    QCOMPARE(reminder.getDate(), QDate());
}

void ReminderTest::test_reminder_empty_setName()
{
    Reminder reminder;
    reminder.setName("test reminder n°1");
    QCOMPARE(reminder.getName(), QString("test reminder n°1"));
    QCOMPARE(reminder.getDate(), QDate());
}

void ReminderTest::test_reminder_empty_setDate()
{
    Reminder reminder;
    reminder.setDate(QDate(1280, 10, 27));
    QCOMPARE(reminder.getDate(), QDate(1280, 10, 27));
    QCOMPARE(reminder.getName(), QString());
}

// Filled Reminder tests
void ReminderTest::test_reminder_filled_create()
{
    Reminder reminder("test reminder", QDate(2003, 6, 12));
    QCOMPARE(reminder.getName(), QString("test reminder"));
    QCOMPARE(reminder.getDate(), QDate(2003, 6, 12));
}

void ReminderTest::test_reminder_filled_getName()
{
    Reminder reminder("test reminder", QDate(2003, 6, 12));
    QCOMPARE(reminder.getName(), QString("test reminder"));
}

void ReminderTest::test_reminder_filled_getDate()
{
    Reminder reminder("test reminder", QDate(2003, 6, 12));
    QCOMPARE(reminder.getDate(), QDate(2003, 6, 12));
}

void ReminderTest::test_reminder_filled_setName()
{
    Reminder reminder("test reminder", QDate(2003, 6, 12));
    reminder.setName("test reminder n°2");
    QCOMPARE(reminder.getName(), QString("test reminder n°2"));
    QCOMPARE(reminder.getDate(), QDate(2003, 6, 12));
}

void ReminderTest::test_reminder_filled_setDate()
{
    Reminder reminder("test reminder", QDate(2003, 6, 12));
    reminder.setDate(QDate(2007, 10, 6));
    QCOMPARE(reminder.getDate(), QDate(2007, 10, 6));
    QCOMPARE(reminder.getName(), QString("test reminder"));
}
