#include "category.h"

/**
 * @brief Constructs a Category object without any parameters.
 */
Category::Category()
    :Category("",QColor(0,0,0))
{}

/**
 * @brief Constructs a Category object with all its member data.
 * @param _name The value of Category name member data.
 * @param _color The value of Category color member data.
 * @param _id The value of Category id member data.
 */
Category::Category(const QString& _name, const QColor& _color)
    : name(_name), color(_color)
{}

/**
 * @brief Destroys the current instance of Category.
 */
Category::~Category()
{}
