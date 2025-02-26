#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <sodium.h>
#include <QMessageBox>

#include "mainwindow.h"
#include "logindialog.h"

/// @brief Program main function.
/// @param argc Main function first argument.
/// @param argv Main function second argument.
/// @return Program exit code.
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if (sodium_init() == -1) {
        QMessageBox::critical(
            nullptr,
            QObject::tr("Erreur d'initialisation"),
            QObject::tr("Erreur lors de l'initialisation de l'application.")
            );
        return -1;
    }

    a.setWindowIcon(QIcon(":/img/icon.png"));
    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "expense_tracking_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }

    QString username;
    loginDialog logindialog(username);
    if (logindialog.exec() == QDialog::Accepted) {
        MainWindow w(username);
        w.show();
        return a.exec();
    }

    return 0;
}
