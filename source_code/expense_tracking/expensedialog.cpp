#include "expensedialog.h"
#include "ui_expensedialog.h"
#include "mainwindow.h"

/**
 * @brief Creates an instance of expensedialog with all its member data.
 * @param parent A pointer on the parent QWidget of the dialog.
 * @param _exists A boolean which indicates whether we are showing/modifying or creating an expense.
 * @param srcExpense If we are showing/modifying an expense, the expense to show/modify.
 * @param _expId If we are showing/modifying an expense, the expense id.
 */
expensedialog::expensedialog(QWidget *parent, bool _exists, Expense *srcExpense, int _expId) :
    QDialog(parent), ui(new Ui::expenseDialog), mw(parent), exists(_exists), expId(_expId)
{
    ui->setupUi(this);
    ui->expenCatComboBox->addItem(tr("Aucune catégorie"), 0);


    MainWindow* _mw=(MainWindow*)mw;
    QMap<int, Category> cats = _mw->exptrc.getCategories();
    for (QMap<int, Category>::iterator it = cats.begin(); it != cats.end(); ++it){
        ui->expenCatComboBox->addItem(cats.value(it.key()).getName(), it.key());
    }

    if (exists)
    {
        setWindowTitle(tr("Modification de dépense"));
        ui->expenTitleLineEdit->setText(srcExpense->getName());
        ui->expenAmountDoubleSpinBox->setValue(srcExpense->getValue());
        ui->expenDateEdit->setDate(srcExpense->getDate());
        ui->expenDescTextEdit->setText(srcExpense->getDescription());
        ui->expenCatComboBox->setCurrentIndex(ui->expenCatComboBox->findData(srcExpense->getCategory()));
    }
    else
    {
        if (srcExpense!=nullptr || _expId!=0)
            throw std::runtime_error("Erreur dans le constructeur de expensedialog: si exists est vrai, il faut obligatoirement préciser srcExpense ET _expId.");
        else{
            ui->expenDateEdit->setDate(QDate::currentDate());
            ui->expenCatComboBox->setCurrentIndex(0);
        }
    }
}

/**
 * @brief Destroys the current instance of expensedialog.
 */
expensedialog::~expensedialog()
{
    delete ui;
}

/**
 * @brief Adds/modifies an Expense to the MainWindow with user's input informations.
 */
void expensedialog::on_dialogButtonBox_accepted()
{
    MainWindow* _mw=(MainWindow*)mw;

    Expense newExpense(ui->expenTitleLineEdit->text(), ui->expenDescTextEdit->toPlainText(), ui->expenCatComboBox->currentData().toInt(), ui->expenDateEdit->date(), ui->expenAmountDoubleSpinBox->value());
    double monthlyBudget =_mw->exptrc.getBudget();
    double totalExpenses =_mw->sumExpense();
    if (totalExpenses + newExpense.getValue() > monthlyBudget) {
        QMessageBox::StandardButton reply = QMessageBox::warning(this,
                                                                  tr("Attention"),
                                                                  tr("Le budget mensuel va être dépassé avec cette dépense.\n\nVoulez-vous quand même l'ajouter ?"),
                                                                  QMessageBox::Yes | QMessageBox::No);

        if (reply == QMessageBox::No) {
            return;
        }
    }
    if (exists)
        _mw->exptrc.updateExpense(expId, newExpense);
    else
        _mw->exptrc.addExpense(newExpense);
    _mw->display();
}

