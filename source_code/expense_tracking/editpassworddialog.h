#ifndef EDITPASSWORDDIALOG_H
#define EDITPASSWORDDIALOG_H

#include <QDialog>
#include "expensetracking.h"

namespace Ui {
class EditPasswordDialog;
}

/**
 * @brief EditPasswordDialog class declaration
 * @note This class is used to handle the EditPasswordDialog window
 */
class EditPasswordDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Constructs a new EditPasswordDialog object
     * @param exptrc A constant reference to an ExpenseTracking object
     * @param parent A pointer to the parent QWidget, defaults to nullptr
     */
    explicit EditPasswordDialog(const ExpenseTracking&, QWidget* = nullptr);

    /**
     * @brief Destructs the EditPasswordDialog object
     */
    ~EditPasswordDialog();

    /**
     * @brief Checks if the given password is valid
     * @param password The password to check
     * @return True if the password is valid, false otherwise
     */
    bool isValidPassword(const QString& password) const;

    /**
     * @brief Checks if the fields are valid
     * @return True if the fields are valid, false otherwise
     */
    bool checkFieldsValidity() const;

    /**
     * @brief The username
     */
    QString username;

private slots:
    /**
     * @brief Handles the CancelButton clicked event
     */
    void on_CancelButton_clicked();

    /**
     * @brief Handles the SaveButton clicked event
     */
    void on_SaveButton_clicked();

    /**
     * @brief Handles the OldPasswordcheckBox state changed event
     * @param arg1 The new state of the checkbox
     */
    void on_OldPasswordcheckBox_stateChanged(const int&);

    /**
     * @brief Handles the NewPasswordcheckBox state changed event
     * @param arg1 The new state of the checkbox
     */
    void on_NewPasswordcheckBox_stateChanged(const int&);

    /**
     * @brief Handles the NewConfirmPasswordcheckBox state changed event
     * @param arg1 The new state of the checkbox
     */
    void on_NewConfirmPasswordcheckBox_stateChanged(const int&);

private:
    Ui::EditPasswordDialog *ui; /**< The UI object for the EditPasswordDialog */

    const ExpenseTracking& exptrc; /**< A constant reference to an ExpenseTracking object */
};

#endif // EDITPASSWORDDIALOG_H
