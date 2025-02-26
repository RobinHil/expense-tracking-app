#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include <QDialog>

#include "userdb.h"

namespace Ui {
class registerDialog;
}

/**
 * @brief The registerDialog class manages the dialog box in which the user can register.
 */
class registerDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Constructs a new registerDialog object.
     * @param parent The parent widget.
     */
    explicit registerDialog(QWidget* =nullptr);

    /**
     * @brief Destructs the registerDialog object.
     */
    ~registerDialog();

private slots:
    /**
     * @brief Slot that handles the state change of seePasswdCheckBox.
     * @param arg1 The new state.
     */
    void on_seePasswdCheckBox_stateChanged(const int&);

    /**
     * @brief Slot that handles the state change of seePasswdConfirmCheckBox.
     * @param arg1 The new state.
     */
    void on_seePasswdConfirmCheckBox_stateChanged(const int&);

    /**
     * @brief Slot that handles the clicked signal of cancelButton.
     */
    void on_cancelButton_clicked();

    /**
     * @brief Slot that handles the clicked signal of saveButton.
     */
    void on_saveButton_clicked();

private:
    /**
     * @brief ui The QT interface object.
     */
    Ui::registerDialog *ui;

    /**
     * @brief userDB The UserDB instance to manage the database part.
     */
    UserDB userDB;

    /**
     * @brief isValidEmail Checks if the given email is valid.
     * @param email The email to check.
     * @return True if the email is valid, false otherwise.
     */
    bool isValidEmail(const QString&) const;

    /**
     * @brief isValidPassword Checks if the given password is valid.
     * @param password The password to check.
     * @return True if the password is valid, false otherwise.
     */
    bool isValidPassword(const QString&) const;

    /**
     * @brief checkFieldsValidity Checks if all fields are valid.
     * @return True if all fields are valid, false otherwise.
     */
    bool checkFieldsValidity() const;
};

#endif // REGISTERDIALOG_H
