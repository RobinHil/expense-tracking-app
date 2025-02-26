#include <QInputDialog>
#include <QMessageBox>
#include <QApplication>
#include <QUuid>

#include "accountdialog.h"
#include "ui_accountdialog.h"
#include "editpassworddialog.h"
#include "hash.h"

/**
 * @brief Constructs an AccountDialog object with the given ExpenseTracking object and parent widget.
 * @param _exptrc The ExpenseTracking object.
 * @param parent The parent widget.
 */
AccountDialog::AccountDialog(const ExpenseTracking& _exptrc, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AccountDialog), exptrc(_exptrc), userdb("sae-suivi-de-depense_app", QUuid::createUuid().toString())
{
    ui->setupUi(this);
    User user=exptrc.getUser();
    ui->usernameEdit->setText(user.getUsername());
    ui->mailEdit->setText(user.getEmail());
    ui->dateEdit->setDate(user.getBirth());
    if(user.getGender()=="f")
        ui->womanRadioButton->setChecked(true);
    else
        ui->manRadioButton->setChecked(true);
}

/**
 * @brief Destructs the AccountDialog object.
 */
AccountDialog::~AccountDialog()
{
    delete ui;
}

/**
 * @brief Opens a dialog to edit the password.
 */
void AccountDialog::on_passwordButton_clicked()
{
    EditPasswordDialog editpassworddialog(exptrc,this);
    editpassworddialog.exec();
}

/**
 * @brief Updates the user's information.
 */
void AccountDialog::on_buttonBox_accepted()
{
    exptrc.updateUser(ui->mailEdit->text(), ui->dateEdit->date(), ui->manRadioButton->isChecked()?"m":"f");
}

/**
 * @brief Sets the woman radio button as checked.
 */
void AccountDialog::on_womanRadioButton_clicked()
{
    ui->manRadioButton->setChecked(false);
}

/**
 * @brief Sets the man radio button as checked.
 */
void AccountDialog::on_manRadioButton_clicked()
{
    ui->womanRadioButton->setChecked(false);
}

/**
 * @brief Removes the user's account.
 */
void AccountDialog::on_removeButton_clicked(){
    bool ok;
    QString password=QInputDialog::getText(this, tr("Mot de passe"), tr("Mot de passe"), QLineEdit::Normal, "", &ok);
    if(ok){
        QMessageBox msgBox;
        QString hash;
        if(userdb.loginUser(exptrc.getUser().getUsername(), hash)){
            if(Hash::verifyArgon2id(hash, password)){
                exptrc.removeUser();
                msgBox.setText(tr("Le compte a bien été supprimé."));
                msgBox.exec();
                qApp->exit();
            }
            else
                msgBox.setText(tr("Mot de passe incorrect."));
        }
        else
            msgBox.setText(tr("Erreur de connexion."));
        msgBox.exec();
    }
}
