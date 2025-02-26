#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QMessageBox>
#include <QCryptographicHash>
#include <QByteArray>
#include <QRandomGenerator>
#include <QDialog>

#include "registerdialog.h"
#include "ui_registerdialog.h"
#include "hash.h"

/**
 * @brief registerDialog::registerDialog creates an instance of RegisterDialog class.
 * @param parent The parent widget of the QDialog.
 */
registerDialog::registerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::registerDialog),
    userDB(UserDB("<db_name>", "register_connection"))
{
    ui->setupUi(this);
    ui->birthDateEdit->setDate(QDate::currentDate());
}

/**
 * @brief registerDialog::~registerDialog destroys the current instance of RegisterDialog.
 */
registerDialog::~registerDialog()
{
    delete ui;
}

/**
 * @brief registerDialog::on_seePasswdCheckBox_stateChanged called when the state of the checkbox changes.
 * @param state Indicates wether the checkbox is checked or not.
 */
void registerDialog::on_seePasswdCheckBox_stateChanged(const int& state)
{
    if(state==Qt::Checked)
        ui->passwdLineEdit->setEchoMode(QLineEdit::Normal);
    else if(state==Qt::Unchecked)
        ui->passwdLineEdit->setEchoMode(QLineEdit::Password);
}

/**
 * @brief registerDialog::on_seePasswdConfirmCheckBox_stateChanged called when the state of the checkbox changes.
 * @param state Indicates wether the checkbox is checked or not.
 */
void registerDialog::on_seePasswdConfirmCheckBox_stateChanged(const int& state)
{
    if(state==Qt::Checked)
        ui->passwdConfirmLineEdit->setEchoMode(QLineEdit::Normal);
    else if(state==Qt::Unchecked)
        ui->passwdConfirmLineEdit->setEchoMode(QLineEdit::Password);
}

/**
 * @brief registerDialog::on_cancelButton_clicked called when the cancel button of the dialog is clicked.
 */
void registerDialog::on_cancelButton_clicked()
{
    close();
}

/**
 * @brief registerDialog::isValidEmail checks if the email address entered by the user is valid.
 * @param email The email address entered by the user.
 * @return Returns true if the email is valid, false instead.
 */
bool registerDialog::isValidEmail(const QString& email) const
{
    const QRegularExpression regex(R"((?:[a-z0-9!#$%&'*+/=?^_`{|}~-]+(?:\.[a-z0-9!#$%&'*+/=?^_`{|}~-]+)*|"(?:[\x01-\x08\x0b\x0c\x0e-\x1f\x21\x23-\x5b\x5d-\x7f]|\\[\x01-\x09\x0b\x0c\x0e-\x7f])*")@(?:(?:[a-z0-9](?:[a-z0-9-]*[a-z0-9])?\.)+[a-z0-9](?:[a-z0-9-]*[a-z0-9])?|\[(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.){3}(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?|[a-z0-9-]*[a-z0-9]:(?:[\x01-\x08\x0b\x0c\x0e-\x1f\x21-\x5a\x53-\x7f]|\\[\x01-\x09\x0b\x0c\x0e-\x7f])+)\]))");
    return regex.match(email).hasMatch();
}

/**
 * @brief registerDialog::isValidPassword checks if the password entered by the user is valid.
 * @param password The password entered by the user.
 * @return Returns true if the password is valid, false instead.
 */
bool registerDialog::isValidPassword(const QString& password) const
{
    const QString specialChars = "!@#$%^&*()-_+={}[]|;:,.<>?/~`éèêàç£¨€";
    const QRegularExpression regex("^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d)(?=.*["+specialChars+"])[a-zA-Z\\d"+specialChars+"]{12,}$");
    return regex.match(password).hasMatch();
}

/**
 * @brief registerDialog::checkFieldsValidity checks if all fields entered by the user are valid.
 * @return Returns true if all fields are valid, false instead.
 */
bool registerDialog::checkFieldsValidity() const {
    QMessageBox errorMsgBox;
    errorMsgBox.setIcon(QMessageBox::Critical);
    errorMsgBox.setWindowTitle(tr("Erreur"));
    errorMsgBox.setStandardButtons(QMessageBox::Ok);

    if (ui->usernameLineEdit->text().isEmpty()) {
        errorMsgBox.setText(tr("Veuillez saisir un nom d'utilisateur."));
        errorMsgBox.exec();
        return false;
    }

    if (ui->passwdLineEdit->text().isEmpty() || !isValidPassword(ui->passwdLineEdit->text())) {
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

    if (ui->passwdConfirmLineEdit->text() != ui->passwdLineEdit->text()) {
        errorMsgBox.setText(
            tr("La confirmation du mot de passe ne correspond pas au mot de passe initial.\n"
               "Veuillez saisir le même mot de passe.")
        );
        errorMsgBox.exec();
        return false;
    }

    if (!isValidEmail(ui->emailLineEdit->text())) {
        errorMsgBox.setText(
            tr("Veuillez saisir un format d'adresse email valide.\n"
               "Par exemple: 'exemple@gogole.fr'.")
        );
        errorMsgBox.exec();
        return false;
    }

    return true;
}

/**
 * @brief registerDialog::on_saveButton_clicked called when the save button of the dialog is clicked.
 * It tries to create the user with the entered fields.
 */
void registerDialog::on_saveButton_clicked()
{
    QMessageBox msgBox;
    msgBox.setStandardButtons(QMessageBox::Ok);

    if (checkFieldsValidity()) {
        if (userDB.userExists(ui->usernameLineEdit->text(), ui->emailLineEdit->text())) {
            msgBox.setIcon(QMessageBox::Critical);
            msgBox.setWindowTitle(tr("Erreur"));
            msgBox.setText(
                tr("Le nom d'utilisateur ou l'adresse email est déjà utilisé.\n"
                   "Veuillez changer les informations saisies ou vous connecter.")
            );
            msgBox.exec();
        } else {
            QString gender = "";
            if (ui->manRadioButton->isChecked())
                gender = "m";
            else if (ui->womanRadioButton->isChecked())
                gender = "f";

            QString hashedPassword = Hash::argon2id(ui->passwdLineEdit->text());
            if (hashedPassword.isNull()) {
                msgBox.setIcon(QMessageBox::Critical);
                msgBox.setWindowTitle(tr("Erreur"));
                msgBox.setText(
                    tr("Erreur lors du hachage du mot de passe.\n"
                       "Veuillez réessayer.")
                );
                msgBox.exec();
            } else {
                if (
                    userDB.registerUser(
                        ui->usernameLineEdit->text(),
                        hashedPassword,
                        ui->birthDateEdit->date(),
                        ui->emailLineEdit->text(),
                        gender
                    )
                ) {
                    msgBox.setIcon(QMessageBox::Information);
                    msgBox.setWindowTitle(tr("Réussite"));
                    msgBox.setText(
                        tr("Inscription réussie !\n"
                           "Vous pouvez maintenant accéder à l'application.")
                    );
                    msgBox.exec();
                    accept();
                } else {
                    msgBox.setIcon(QMessageBox::Critical);
                    msgBox.setWindowTitle(tr("Erreur"));
                    msgBox.setText(
                        tr("Erreur lors de l'inscription.\n"
                           "Veuillez vérifier votre connexion internet puis réessayer.")
                    );
                    msgBox.exec();
                }
            }
        }
    }
}

