#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QMap>
#include <QDateTime>

#include "userdb.h"

namespace Ui {
class loginDialog;
}

/**
 * @brief The loginDialog class manages the dialog box in which the user can login.
 */
class loginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit loginDialog(QString&, QWidget* =nullptr);
    ~loginDialog();

private slots:
    void on_seePasswdCheckBox_stateChanged(const int&);
    void on_registerButton_clicked();
    void on_loginButton_clicked();

private:
    /**
     * @brief ui The QT interface object.
     */
    Ui::loginDialog *ui;

    /**
     * @brief userDB The UserDB instance to manage the database part.
     */
    UserDB userDB;

    /**
     * @brief username The username which is changed if the user connects successfully.
     */
    QString& username;

};

#endif // LOGINDIALOG_H
