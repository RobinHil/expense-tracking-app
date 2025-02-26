#include "categorytest.h"
#include "category.h"

CategoryTest::CategoryTest(QObject *parent)
    : QObject(parent)
{}

// Empty Category tests
void CategoryTest::test_category_empty_create()
{
    Category category;
    QCOMPARE(category.getName(), QString());
    QCOMPARE(category.getColor(), QColor(0,0,0));
}

void CategoryTest::test_category_empty_getName()
{
    Category category;
    QCOMPARE(category.getName(), QString());
}

void CategoryTest::test_category_empty_getColor()
{
    Category category;
    QCOMPARE(category.getColor(), QColor(0,0,0));
}

void CategoryTest::test_category_empty_setName()
{
    Category category;
    category.setName("test category 1");
    QCOMPARE(category.getName(), QString("test category 1"));
    QCOMPARE(category.getColor(), QColor(0,0,0));
}

void CategoryTest::test_category_empty_setColor()
{
    Category category;
    category.setColor(QColor(255, 255, 20));
    QCOMPARE(category.getName(), QString());
    QCOMPARE(category.getColor(), QColor(255, 255, 20));
}

// Filled Category tests
void CategoryTest::test_category_filled_create()
{
    Category category("test category", QColor(128, 250, 12));
    QCOMPARE(category.getName(), QString("test category"));
    QCOMPARE(category.getColor(), QColor(128, 250, 12));
}

void CategoryTest::test_category_filled_getName()
{
    Category category("test category", QColor(128, 250, 12));
    QCOMPARE(category.getName(), QString("test category"));
}

void CategoryTest::test_category_filled_getColor()
{
    Category category("test category", QColor(128, 250, 12));
    QCOMPARE(category.getColor(), QColor(128, 250, 12));
}

void CategoryTest::test_category_filled_setName()
{
    Category category("test category", QColor(128, 250, 12));
    category.setName("test category 2");
    QCOMPARE(category.getName(), QString("test category 2"));
    QCOMPARE(category.getColor(), QColor(128, 250, 12));
}

void CategoryTest::test_category_filled_setColor()
{
    Category category("test category", QColor(128, 250, 12));
    category.setColor(QColor(10, 186, 181));
    QCOMPARE(category.getName(), QString("test category"));
    QCOMPARE(category.getColor(), QColor(10, 186, 181));
}
