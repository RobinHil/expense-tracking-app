#include <QMessageBox>
#include <QRegularExpression>

#include "logindialog.h"
#include "ui_logindialog.h"
#include "registerdialog.h"
#include "hash.h"

/**
 * @brief loginDialog::loginDialog creates an instance of LoginDialog class.
 * @param parent The parent widget of the QDialog.
 */
loginDialog::loginDialog(QString& _username, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::loginDialog),
    userDB(UserDB("<db_name>", "login_connection")),
    username(_username)
{
    ui->setupUi(this);
}

/**
 * @brief loginDialog::~loginDialog destroys the current instance of LoginDialog.
 */
loginDialog::~loginDialog()
{
    delete ui;
}

/**
 * @brief loginDialog::on_seePasswdCheckBox_stateChanged called when the state of the checkbox changes.
 * @param state Indicates wether the checkbox is checked or not.
 */
void loginDialog::on_seePasswdCheckBox_stateChanged(const int& state)
{
    if(state==Qt::Checked)
        ui->passwdLineEdit->setEchoMode(QLineEdit::Normal);
    else if(state==Qt::Unchecked)
        ui->passwdLineEdit->setEchoMode(QLineEdit::Password);

}

/**
 * @brief loginDialog::on_registerButton_clicked Opens a register dialog.
 */
void loginDialog::on_registerButton_clicked()
{
    registerDialog registerDialog(this);
    registerDialog.exec();
}

/**
 * @brief loginDialog::on_loginButton_clicked called when the login button of the dialog is clicked.
 * It tries to login the user with the entered fields.
 */
void loginDialog::on_loginButton_clicked()
{
    QMessageBox msgBox;
    msgBox.setStandardButtons(QMessageBox::Ok);

    QString username = ui->usernameLineEdit->text();
    if (userDB.isAccountLocked(username)) {
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setWindowTitle(tr("Erreur"));
        msgBox.setText(
            tr("Ce compte est temporairement bloqué !\n"
               "Il y a eu de trop nombreuses tentatives de connexion infructueuses.\n"
               "Le bloquage dure 5 minutes, veuillez réessayer plus tard.")
        );
        msgBox.exec();
        return;
    } else {
        if (userDB.userExists(username, username)) {
            QString hashedPassword;
            if (userDB.loginUser(username, hashedPassword)) {
                if (Hash::verifyArgon2id(hashedPassword, ui->passwdLineEdit->text())) {
                    msgBox.setIcon(QMessageBox::Information);
                    msgBox.setWindowTitle(tr("Réussite"));
                    msgBox.setText(
                        tr("Connexion réussie !\n"
                           "Vous allez être redirigé vers l'application.")
                    );
                    msgBox.exec();
                    userDB.resetAuthAttempts(username);
                    this->username = username;
                    accept();
                } else {
                    userDB.incrementLoginAttempts(username);
                    msgBox.setIcon(QMessageBox::Critical);
                    msgBox.setWindowTitle(tr("Erreur"));
                    msgBox.setText(
                        tr("Erreur lors de la connexion.\n"
                           "Veuillez vérifier l'identifiant et le mot de passe puis réessayer.")
                    );
                    msgBox.exec();
                }
            } else {
                userDB.incrementLoginAttempts(username);
                msgBox.setIcon(QMessageBox::Critical);
                msgBox.setWindowTitle(tr("Erreur"));
                msgBox.setText(
                    tr("Erreur lors de la connexion.\n"
                       "Veuillez réessayer plus tard.")
                );
                msgBox.exec();
            }
        } else {
            userDB.incrementLoginAttempts(username);
            msgBox.setIcon(QMessageBox::Critical);
            msgBox.setWindowTitle(tr("Erreur"));
            msgBox.setText(
                tr("Erreur lors de la connexion.\n"
                   "Veuillez vérifier l'identifiant et le mot de passe puis réessayer.")
            );
            msgBox.exec();
        }
    }
}


