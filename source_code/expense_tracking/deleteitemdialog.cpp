#include "deleteitemdialog.h"
#include "ui_deleteitemdialog.h"
#include "mainwindow.h"
#include "expensetracking.h"

/**
 * @brief Constructor for DeleteItemDialog.
 * @param _parent The parent widget, typically the main window.
 */
DeleteItemDialog::DeleteItemDialog(QWidget *_parent, const QString& label, const QMap<int, QString>& items,void (ExpenseTracking::*_deleteItem)(const unsigned&)const) :
    QDialog(_parent), ui(new Ui::DeleteItemDialog), parent((MainWindow*)_parent), deleteItem(_deleteItem)
{
    ui->setupUi(this);

    ui->label->setText(label);

    ui->itemComboBox->addItem(tr("Aucun"), 0);

    for (QMap<int, QString>::const_iterator it = items.begin(); it != items.end(); ++it) {
        ui->itemComboBox->addItem(items.value(it.key()), it.key());
    }
}

/**
 * @brief Destructor for DeleteItemDialog.
 */
DeleteItemDialog::~DeleteItemDialog()
{
    delete ui;
}

/**
 * @brief Slot called when the accept button on the dialog is clicked.
 *        Removes the selected category and updates the display.
 */
void DeleteItemDialog::on_dialogButtonBox_accepted()
{
    (parent->exptrc.*(deleteItem))(ui->itemComboBox->currentData().toInt());
    parent->display();
    parent->displayCategory();
}

