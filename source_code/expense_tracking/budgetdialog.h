#ifndef BUDGETDIALOG_H
#define BUDGETDIALOG_H

#include <QDialog>

namespace Ui {
class BudgetDialog;
}

/**
 * @class BudgetDialog
 * @brief Represents a dialog window for budget-related interactions.
 */
class BudgetDialog : public QDialog
{
    Q_OBJECT
    /**
     * @brief The current budget amount.
     */
    double budget;

public:
    /**
     * @brief Constructor for BudgetDialog.
     * @param parent The parent QWidget for this dialog.
     * @param _somme The initial amount to be displayed.
     * @param budget The initial budget.
     */
    explicit BudgetDialog(QWidget *parent = nullptr,double _somme=0.0,double budget=0.0);

    /**
     * @brief Displays data in the user interface.
     */
    void affichage();

    /**
     * @brief Destructor for BudgetDialog.
     */
    ~BudgetDialog();

    /**
     * @return The current budget.
     */
    inline const double& getBudget() const {return budget;};

    /**
     * @brief Sets the budget to a new value.
     */
    void setBudget();

private slots:

    /**
     * @brief Slot called when the accept button of the dialog is clicked.
     */
    void on_dialogButtonBox_accepted();

private:
    /**
     * @brief Pointer to the user interface setup for this dialog.
     */
    Ui::BudgetDialog *ui;

    /**
     * @brief Variable to store a numeric value, potentially representing a sum or total.
     */
    double somme;

    /**
     * @brief Pointer to a parent or associated widget.
     * 'mw' is likely used to refer to the main window or a parent widget of this dialog.
     */
    QWidget* mw;
};

#endif // BUDGETDIALOG_H
