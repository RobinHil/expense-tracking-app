#include <QMessageBox>
#include <QRegularExpression>

#include "editpassworddialog.h"
#include "ui_editpassworddialog.h"
#include "expensetracking.h"
#include "hash.h"

/**
 * @brief Constructs an EditPasswordDialog object.
 * @param _exptrc Reference to an ExpenseTracking object.
 * @param parent Pointer to the parent QWidget.
 */
EditPasswordDialog::EditPasswordDialog(const ExpenseTracking& _exptrc, QWidget *parent)
    : QDialog(parent),
    ui(new Ui::EditPasswordDialog),
    exptrc(_exptrc)
{
    ui->setupUi(this);

    User user = exptrc.getUser();
    username = user.getUsername();
}

/**
 * @brief Destructs an EditPasswordDialog object.
 */
EditPasswordDialog::~EditPasswordDialog()
{
    delete ui;
}

/**
 * @brief Closes the dialog.
 */
void EditPasswordDialog::on_CancelButton_clicked()
{
    close();
}

/**
 * @brief Checks if the given password is valid.
 * @param password The password to check.
 * @return True if the password is valid, false otherwise.
 */
bool EditPasswordDialog::isValidPassword(const QString& password) const
{
    const QString specialChars = "!@#$%^&*()-_+={}[]|;:,.<>?/~`éèêàç£¨€";
    const QRegularExpression regex("^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d)(?=.*["+specialChars+"])[a-zA-Z\\d"+specialChars+"]{12,}$");
    return regex.match(password).hasMatch();
}

/**
 * @brief Checks if the fields in the dialog are valid.
 * @return True if the fields are valid, false otherwise.
 */
bool EditPasswordDialog::checkFieldsValidity() const {
    QMessageBox errorMsgBox;
    errorMsgBox.setIcon(QMessageBox::Critical);
    errorMsgBox.setWindowTitle(tr("Erreur"));
    errorMsgBox.setStandardButtons(QMessageBox::Ok);

    if (ui->NewPasswdLineEdit->text().isEmpty() || !isValidPassword(ui->NewPasswdLineEdit->text())) {
        errorMsgBox.setText(
            tr("Veuillez saisir un mot de passe valide.\n\n"
               "Un mot de passe valide respecte les conditions suivantes:\n"
               "        - Un minimum de 12 caractères\n"
               "        - Au moins une majuscule\n"
               "        - Au moins une minuscule\n"
               "        - Au moint un caractère spécial:\n"
               "                !@#$%^&*()-_+={}[]|;:,.<>?/~`éèêàç£¨€\n\n")
            );
        errorMsgBox.exec();
        return false;
    }

    if (ui->NewPasswdConfirmationLineEdit_2->text() != ui->NewPasswdLineEdit->text()) {
        errorMsgBox.setText(
            tr("La confirmation du mot de passe ne correspond pas au mot de passe initial.\n"
               "Veuillez saisir le même mot de passe.")
            );
        errorMsgBox.exec();
        return false;
    }
    return true;
}

/**
 * @brief Handles the save button click event.
 */
void EditPasswordDialog::on_SaveButton_clicked()
{
    if (checkFieldsValidity()) {
        QString oldPassword = ui->OldPasswordLineEdit->text();
        QString newHashedPassword = Hash::argon2id(ui->NewPasswdLineEdit->text());
        QString storedHashedPassword;
        if (exptrc.getUserPassword(storedHashedPassword))
            if (Hash::verifyArgon2id(storedHashedPassword, oldPassword))
                if (exptrc.updatePassword(newHashedPassword)){
                    QMessageBox::information(this, tr("Réussite"), tr("Le mot de passe a bien été modifié."));
                    accept();
                }
                else
                    QMessageBox::critical(this, tr("Erreur"), tr("Erreur de modification du mot de passe."));
            else
                QMessageBox::critical(this, tr("Erreur"), tr("L'ancien mot de passe est incorrect. Veuillez réessayer."));
        else
            QMessageBox::critical(this, tr("Erreur"), tr("Erreur de connexion. Veuillez réessayer."));
    }
}

/**
 * @brief Handles the old password checkbox state change event.
 * @param state The new state of the checkbox.
 */
void EditPasswordDialog::on_OldPasswordcheckBox_stateChanged(const int& state)
{
    if(state==Qt::Checked)
        ui->OldPasswordLineEdit->setEchoMode(QLineEdit::Normal);
    else if(state==Qt::Unchecked)
        ui->OldPasswordLineEdit->setEchoMode(QLineEdit::Password);
}

/**
 * @brief Handles the new password checkbox state change event.
 * @param state The new state of the checkbox.
 */
void EditPasswordDialog::on_NewPasswordcheckBox_stateChanged(const int& state)
{
    if(state==Qt::Checked)
        ui->NewPasswdLineEdit->setEchoMode(QLineEdit::Normal);
    else if(state==Qt::Unchecked)
        ui->NewPasswdLineEdit->setEchoMode(QLineEdit::Password);
}

/**
 * @brief Handles the new confirm password checkbox state change event.
 * @param state The new state of the checkbox.
 */
void EditPasswordDialog::on_NewConfirmPasswordcheckBox_stateChanged(const int& state)
{
    if(state==Qt::Checked)
        ui->NewPasswdConfirmationLineEdit_2->setEchoMode(QLineEdit::Normal);
    else if(state==Qt::Unchecked)
        ui->NewPasswdConfirmationLineEdit_2->setEchoMode(QLineEdit::Password);
}
