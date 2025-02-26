#ifndef CATEGORY_H
#define CATEGORY_H

#include <QString>
#include <QColor>

/**
 * @brief Represents a category.
 */
class Category
{
    /** @brief Category name. */
    QString name;

    /** @brief Category color. */
    QColor color;

public:
    /**
     * @brief Constructs an empty Category object.
     */
    Category();

    /**
     * @brief Constructs a Category object with the given name and color.
     * @param name Category name.
     * @param color Category color.
     */
    Category(const QString&, const QColor&);

    /**
     * @brief Destructs the Category object.
     */
    ~Category();

    /**
     * @brief Returns the current instance name.
     * @return Current instance name.
     */
    inline const QString& getName() const {return name;};

    /**
     * @brief Sets a new name value.
     * @param _name New name value.
     */
    inline void setName(const QString& _name) {name = _name;};

    /**
     * @brief Returns the current instance color.
     * @return Current instance color.
     */
    inline const QColor& getColor() const {return color;};

    /**
     * @brief Sets a new color value.
     * @param _color New color value.
     */
    inline void setColor(const QColor& _color) {color = _color;};
};

#endif // CATEGORY_H
