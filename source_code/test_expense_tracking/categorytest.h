#ifndef CATEGORYTEST_H
#define CATEGORYTEST_H

#include <QObject>
#include <QTest>

/**
 * @class CategoryTest
 * @brief This class is used to test the Category class.
 *
 * This class inherits from QObject and is used to test the functionality of the Category class.
 */
class CategoryTest : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief Construct a new Category Test object.
     *
     * @param parent The parent object.
     */
    CategoryTest(QObject* parent = nullptr);

private slots:
    // Empty Category tests

    /**
     * @brief Test the creation of an empty Category object.
     */
    void test_category_empty_create();

    /**
     * @brief Test the getName function of an empty Category object.
     */
    void test_category_empty_getName();

    /**
     * @brief Test the getColor function of an empty Category object.
     */
    void test_category_empty_getColor();

    /**
     * @brief Test the setName function of an empty Category object.
     */
    void test_category_empty_setName();

    /**
     * @brief Test the setColor function of an empty Category object.
     */
    void test_category_empty_setColor();

    // Filled Category tests

    /**
     * @brief Test the creation of a filled Category object.
     */
    void test_category_filled_create();

    /**
     * @brief Test the getName function of a filled Category object.
     */
    void test_category_filled_getName();

    /**
     * @brief Test the getColor function of a filled Category object.
     */
    void test_category_filled_getColor();

    /**
     * @brief Test the setName function of a filled Category object.
     */
    void test_category_filled_setName();

    /**
     * @brief Test the setColor function of a filled Category object.
     */
    void test_category_filled_setColor();
};

#endif // CATEGORYTEST_H
