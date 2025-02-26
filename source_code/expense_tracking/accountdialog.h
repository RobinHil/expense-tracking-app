#ifndef ACCOUNTDIALOG_H
#define ACCOUNTDIALOG_H

#include <QDialog>

#include "expensetracking.h"
#include "userdb.h"

namespace Ui {
class AccountDialog;
}

/**
 * @brief The AccountDialog class provides a dialog for managing user account settings.
 */
class AccountDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Constructs an AccountDialog object with the given ExpenseTracking reference and parent widget.
     * @param _exptrc A constant reference to an ExpenseTracking object.
     * @param parent A pointer to the parent widget.
     */
    explicit AccountDialog(const ExpenseTracking& _exptrc, QWidget *parent = nullptr);

    /**
     * @brief Destructs the AccountDialog object.
     */
    ~AccountDialog();

private slots:
    /**
     * @brief Handles the clicked signal from the passwordButton.
     */
    void on_passwordButton_clicked();

    /**
     * @brief Handles the accepted signal from the buttonBox.
     */
    void on_buttonBox_accepted();

    /**
     * @brief Handles the clicked signal from the womanRadioButton.
     */
    void on_womanRadioButton_clicked();

    /**
     * @brief Handles the clicked signal from the manRadioButton.
     */
    void on_manRadioButton_clicked();

    /**
     * @brief Handles the clicked signal from the removeButton.
     */
    void on_removeButton_clicked();

private:
    Ui::AccountDialog *ui;  /**< A pointer to the UI object of AccountDialog. */

    const ExpenseTracking& exptrc;  /**< A constant reference to an ExpenseTracking object. */
    UserDB userdb;  /**< An object of UserDB class. */
};

#endif // ACCOUNTDIALOG_H
