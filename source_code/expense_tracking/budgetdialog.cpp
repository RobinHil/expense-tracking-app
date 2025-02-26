#include "budgetdialog.h"
#include "ui_budgetdialog.h"
#include "mainwindow.h"

/**
 * @brief Constructor for BudgetDialog.
 * @param parent The parent widget, typically the main window.
 * @param _somme The initial sum to be displayed.
 * @param _budget The initial budget.
 */
BudgetDialog::BudgetDialog(QWidget *parent, double _somme, double _budget) :
    QDialog(parent), budget(_budget),
    ui(new Ui::BudgetDialog), somme(_somme), mw(parent)
{
    ui->setupUi(this);
    affichage();
}

/**
 * @brief Destructor for BudgetDialog.
 */
BudgetDialog::~BudgetDialog()
{
    delete ui;
}

/**
 * @brief Displays the budget information in the dialog.
 */
void BudgetDialog::affichage()
{
    MainWindow* _mw=(MainWindow*)mw;
    double budget_b=_mw->exptrc.getBudget();
    ui->initBudgetButtonBox->setValue(budget_b);
    ui->totalExpenValueLabel->setText(QString::number(somme)+"€");
    ui->remainBudgetValueLabel->setText(QString::number(budget_b - somme)+"€");
}

/**
 * @brief Sets the budget to the value entered in the dialog.
 */
void BudgetDialog::setBudget()
{
    MainWindow* _mw=(MainWindow*)mw;
    double nouveauBudget = ui->initBudgetButtonBox->value();
    budget = nouveauBudget;
    _mw->exptrc.updateBudget(nouveauBudget);
}

/**
 * @brief Slot called when the accept button on the dialog is clicked.
 *        Saves the new budget value.
 */
void BudgetDialog::on_dialogButtonBox_accepted() {
    setBudget();
}
