#ifndef EXPENSEDIALOG_H
#define EXPENSEDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include "expense.h"

namespace Ui {
class expenseDialog;
}
/** @brief The expensedialog class provides a dialog for managing expenses. */
class expensedialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Constructor for expensedialog.
     * @param parent The parent widget, typically the main window.
     * @param exists Flag indicating if the expense already exists.
     * @param expense Pointer to an Expense object, nullptr if creating a new expense.
     * @param expId The ID of the expense, 0 if creating a new expense.
     */
    explicit expensedialog(QWidget *parent =nullptr, bool =false, Expense* =nullptr, int =0);

    /** @brief Destructor for expensedialog. */
    ~expensedialog();

private slots:
    /** @brief Slot that is called when the accept button on the dialog is clicked. */
    void on_dialogButtonBox_accepted();

private:
    /** @brief Pointer to the user interface setup for this dialog. */
    Ui::expenseDialog *ui;

    /** @brief Pointer to a parent or associated widget. */
    QWidget* mw;

    /** @brief Flag indicating the existence of the dialog. */
    bool exists;

    /** @brief Identifier for the expense associated with the dialog. */
    int expId;
};

#endif // EXPENSEDIALOG_H
