#ifndef SHOWCATEGORYDIALOG_H
#define SHOWCATEGORYDIALOG_H

#include <QDialog>

namespace Ui {
/**
 * @brief The ShowCategoryDialog class represents a dialog for showing categories.
 */
class ShowCategoryDialog;
}

/**
 * @brief The ShowCategoryDialog class provides a dialog for displaying categories.
 */
class ShowCategoryDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Constructor for ShowCategoryDialog.
     * @param parent The parent widget, typically the main window.
     */
    explicit ShowCategoryDialog(QWidget* =nullptr);

    /**
     * @brief Displays categories in the dialog.
     */
    void afficherCategory();

    /**
     * @brief Destructor for ShowCategoryDialog.
     */
    ~ShowCategoryDialog();

private:

    /**
     * @brief User interface for the ShowCategoryDialog.
     */
    Ui::ShowCategoryDialog *ui;

    /**
     * @brief Pointer to the main window.
     */
    QWidget* mw;
};

#endif // SHOWCATEGORYDIALOG_H
