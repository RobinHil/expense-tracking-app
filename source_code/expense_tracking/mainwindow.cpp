#include <QMessageBox>
#include <QInputDialog>
#include <QColorDialog>
#include <QVariant>
#include <QDateEdit>
#include <QDialog>
#include <QDialogButtonBox>
#include <QDateEdit>
#include <QFileDialog>
#include <QVBoxLayout>
#include <QTextStream>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "expensedialog.h"
#include "showcategorydialog.h"
#include "deleteitemdialog.h"
#include "budgetdialog.h"
#include "reminder.h"
#include "chartsdialog.h"
#include "accountdialog.h"

/**
 * @brief Creates an instance of MainWindow.
 *
 * @param parent MainWindow instance parent widget.
 */
MainWindow::MainWindow(const QString& username, QWidget *parent)
    : QMainWindow(parent), exptrc(username, "<db_name>", "main_connection"), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Display expired reminders
    checkExpired();

    // Set table widget layout
    ui->expenTableWidget->verticalHeader()->setVisible(false);
    ui->expenTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->expenTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->expenTableWidget->hideColumn(0);

    // Display
    displayCategory();

    display();
}

/**
 * @brief Destroys the current instance of MainWindow.
 */
MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * @brief Sets an item in the expense table widget.
 *
 * This function creates a new QTableWidgetItem with the given string and sets it
 * in the specified row and column of the expense table. The created item is made
 * non-editable, meaning it cannot be modified by the user directly through the GUI.
 *
 * @param row The row index where the item should be placed.
 * @param col The column index where the item should be placed.
 * @param s The text content to be set in the table item.
 *
 * @note This function assumes that 'ui->expenTableWidget' is a valid pointer to a QTableWidget.
 */
void MainWindow::setItem(int row, int col, const QString& s) const{
    QTableWidgetItem* item = new QTableWidgetItem(s);
    item->setFlags(item->flags() ^ Qt::ItemIsEditable);
    ui->expenTableWidget->setItem(row, col, item);
}

/**
 * @brief Retrieves the ID from a specified row in the expense table.
 * @param row The row index from which the ID should be retrieved.
 * @return int The integer ID found in the first column of the specified row.
 */
int MainWindow::getRowId(int row) const{
    return ui->expenTableWidget->item(row,0)->text().toInt();
}

/**
 * @brief Gets the type of the date.
 * @return int The type of the date (day, month, or year).
 */
int MainWindow::getDateType() const{
    // Get type of the date (day, month or year)
    int dateType = 0;
    if(ui->dayRadioButton->isChecked()){
        dateType = 1;
    }else if(ui->monthRadioButton->isChecked()){
        dateType = 2;
    }else if(ui->yearRadioButton->isChecked()){
        dateType = 3;
    }
    return dateType;
}

/**
 * @brief Displays the list of expenses in the UI interface.
 */
void MainWindow::display() const
{
    // Clear tableWidget
    ui->expenTableWidget->clearContents();
    ui->expenTableWidget->setRowCount(0);

    // Get type of the date
    int dateType=getDateType();

    // Get categories
    QMap<int, Category> cats = exptrc.getCategories();
    // Get corresponding expenses
    QVector<QPair<int,Expense>> exp = exptrc.getExpenses(ui->categoryChoiceComboBox->currentData().toInt(), ui->searchLineEdit->text(), dateType, ui->expenCalendarWidget->selectedDate());

    // Display each expense in a row of table widget
    for (QVector<QPair<int,Expense>>::iterator it = exp.begin(); it != exp.end(); ++it) {
        const Expense& e = it->second;
        // Get last row
        int rowCount = ui->expenTableWidget->rowCount();
        // Add a row
        ui->expenTableWidget->insertRow(rowCount);
        // Set row content
        setItem(rowCount, 0, QString::number(it->first));
        setItem(rowCount, 1, e.getName());
        setItem(rowCount, 2, QString::number(e.getValue()) + "€");
        setItem(rowCount, 3, e.getDate().toString("dd/MM/yyyy"));
        setItem(rowCount, 4, (e.getCategory() == 0 ? tr("Aucune") : cats.value(e.getCategory()).getName()));
    }

    // Display Budget
    loadBudget();
}

/**
 * @brief Displays the list of categories in the UI interface.
 */
void MainWindow::displayCategory()const{
    // Clear the combo box
    ui->categoryChoiceComboBox->clear();
    // Add default entry
    ui->categoryChoiceComboBox->addItem(tr("Toutes les catégories"),0);

    // Display all categories
    QMap<int, Category> cats = exptrc.getCategories();
    for (QMap<int, Category>::iterator it = cats.begin(); it != cats.end(); ++it){
        ui->categoryChoiceComboBox->addItem(cats.value(it.key()).getName(),it.key());
    }
}

/**
 * @brief Opens expense adding dialog.
 */
void MainWindow::on_expenAddButton_clicked()
{
    // Display expenseDialog
    expensedialog expenseDialog(this);
    expenseDialog.exec();
}

/**
 * @brief Opens about message box.
 */
void MainWindow::on_aboutAction_triggered()
{
    // Display about window
    QMessageBox::information(
        this,
        tr("À propos"),
        tr(
            "Suivi de dépenses\n\n"
            "Application de suivi de dépenses personnelles catégorisées."
          )
        );
}

/**
 * @brief Closes the application.
 */
void MainWindow::on_exitAction_triggered()
{
    qApp->quit();
}

/**
 * @brief Deletes selected expense in the list.
 */
void MainWindow::on_expenDeleteButton_clicked()
{
    // Get alls ID to remove
    QSet<int> ids;
    for(const QTableWidgetItem *item : ui->expenTableWidget->selectedItems())
    {
        ids.insert(getRowId(item->row()));
    }
    // Remove expenses by id
    for(const int id: ids.values())
        exptrc.removeExpense(id);
    // Refresh screen display
    display();
}

/**
 * @brief Opens user manual message box.
 */
void MainWindow::on_useAction_triggered()
{
    QString message = tr("Suivi de dépenses.<br/><br/>"
                         "Un manuel d'utilisation détaillé est disponible à l'adresse <i><url_manuel_utilisation></i>.<br/>"
                         "Vous pouvez y accéder depuis le lien ci-dessous.<br/><br/>"
                         "Manuel d'utilisation: <a href='<url_manuel_utilisation>'>cliquez ici</a>");

    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle(tr("Utilisation"));
    dialog->setModal(true);

    QVBoxLayout *layout = new QVBoxLayout(dialog);
    QLabel *iconLabel = new QLabel(dialog);
    iconLabel->setPixmap(style()->standardIcon(QStyle::SP_MessageBoxInformation).pixmap(QSize(48, 48)));
    layout->addWidget(iconLabel, 0, Qt::AlignCenter);

    QTextBrowser *textBrowser = new QTextBrowser(dialog);
    textBrowser->setOpenExternalLinks(true);
    textBrowser->setHtml(message);
    layout->addWidget(textBrowser);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok, dialog);
    layout->addWidget(buttonBox);

    QObject::connect(buttonBox, &QDialogButtonBox::accepted, dialog, &QDialog::accept);

    dialog->exec();
}

/**
 * @brief Opens contact message box.
 */
void MainWindow::on_contactAction_triggered()
{
    // Display contact informations
    QMessageBox::information(
        this,
        tr("Contacts"),
        tr(
            "Suivi de dépenses"
          )
        );
}

/**
 * @brief Opens category showing dialog.
 */
void MainWindow::on_showCatAction_triggered()
{
    // Display category dialog
    ShowCategoryDialog dialog(this);
    dialog.exec();
}

/**
 * @brief Shows only expenses from currently selected category.
 */
void MainWindow::on_categoryChoiceComboBox_currentIndexChanged(int)
{
    // Refresh screen
    display();
}

/**
 * @brief Opens category adding message boxes.
 */
void MainWindow::on_addCatAction_triggered()
{
    bool ok;
    // Answer categorie name
    QString categoryName = QInputDialog::getText(this, tr("Ajouter une catégorie"),
                                                 tr("Nom de la catégorie"), QLineEdit::Normal,
                                                 QString(), &ok);
    // Check user answer
    if (ok && !categoryName.isEmpty()) {
        // Answer a color
        QColor color = QColorDialog::getColor(Qt::white, this, tr("Choisissez une couleur pour la catégorie"));

        // Check user answer
        if(color.isValid()) {
            // Add the category to the database
            exptrc.addCategory(Category(categoryName, color));

            // Refresh category
            displayCategory();
        }
    }
}

/**
 * @brief Opens category removing message boxes.
 */
void MainWindow::on_deleteCatAction_triggered()
{
    QMap<int, Category> cats = exptrc.getCategories();
    QMap<int, QString> items;
    for (QMap<int, Category>::iterator it = cats.begin(); it != cats.end(); ++it)
        items[it.key()]=cats.value(it.key()).getName();
    // Display a window
    DeleteItemDialog dialog(this, tr("Sélectionner la catégorie à supprimer"), items, &ExpenseTracking::removeCategory);
    dialog.exec();
}

/**
 * @brief Slot for handling selection changes in the expense calendar widget.
 */
void MainWindow::on_expenCalendarWidget_selectionChanged()
{
    display();
}

/**
 * @brief Slot for handling clicks on the 'Month' radio button.
 */
void MainWindow::on_monthRadioButton_clicked()
{
    display();
}
/**
 * @brief Slot for handling clicks on the 'Day' radio button.
 */
void MainWindow::on_dayRadioButton_clicked()
{
    display();
}
/**
 * @brief Slot for handling clicks on the 'Year' radio button.
 */
void MainWindow::on_yearRadioButton_clicked()
{
    display();
}

/**
 * @brief Slot for handling double-click events on cells in the expense table widget.
 * @param row The row index of the cell that was double-clicked.
 */
void MainWindow::on_expenTableWidget_cellDoubleClicked(int row)
{
    // Get clicked row
    int id = getRowId(row);
    // Get selected expense
    Expense exp = exptrc.getExpense(id);
    // Display expense
    expensedialog expenseDialog(this, true, &exp, id);
    expenseDialog.exec();
}

/**
 * @brief Handles the addition of a new reminder.
 *        It prompts the user for the reminder name and date, and then adds it to the system.
 */
void MainWindow::on_addRemAction_triggered(){
    bool ok;
    // Answer the name of the reminder
    QString nom = QInputDialog::getText(this, tr("Ajouter un rappel"),
                                        tr("Nom du rappel"), QLineEdit::Normal,
                                        QString(), &ok);
    // Check user answer
    if (ok && !nom.isEmpty()){
        // Display date chooser
        QDialog dialog(this);
        QDateEdit dateEdit;
        dateEdit.setCalendarPopup(true);
        dateEdit.setDate(QDate::currentDate());
        QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                                   Qt::Horizontal, &dialog);
        connect(&buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
        connect(&buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);
        QVBoxLayout layout;
        layout.addWidget(&dateEdit);
        layout.addWidget(&buttonBox);
        dialog.setLayout(&layout);
        // Check user answer
        if (dialog.exec() == QDialog::Accepted) {
            // Create reminder
            QDate date = dateEdit.date();
            Reminder rappel(nom, date);
            // Add reminder to database
            exptrc.addReminder(rappel);
        }
    }
}

/**
 * @brief Provides functionality to delete a selected reminder.
 *        It lists all reminders for the user to select and delete.
 */
void MainWindow::on_delRemAction_triggered() {
    QMap<int, Reminder> rems = exptrc.getReminders();
    QMap<int, QString> items;
    for (QMap<int, Reminder>::iterator it = rems.begin(); it != rems.end(); ++it)
        items[it.key()]=rems.value(it.key()).getName();
    // Display a window
    DeleteItemDialog dialog(this, tr("Sélectionner le rappel à supprimer"), items, &ExpenseTracking::removeReminder);
    dialog.exec();
}

/**
 * @brief Opens a dialog to display all reminders.
 */
void MainWindow::on_showRemAction_triggered()
{
    QDialog dialog(this);
    dialog.setWindowTitle(tr("Rappels"));

    QVBoxLayout* layout = new QVBoxLayout(&dialog);

    QListWidget* listWidget = new QListWidget(&dialog);
    layout->addWidget(listWidget);

    QMap<int, Reminder> reminders = exptrc.getReminders();
    for (auto it = reminders.begin(); it != reminders.end(); ++it) {
        const Reminder &reminder = it.value();
        listWidget->addItem(reminder.getName() + " - " + QLocale().toString(reminder.getDate()));
    }

    QDialogButtonBox* buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok, &dialog);
    layout->addWidget(buttonBox);

    connect(buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);

    dialog.exec();
}

/**
 * @brief Slot for handling the 'Total Expense' button click event.
 */
double MainWindow::sumExpense()const{
    return exptrc.getExpensesSum(2,ui->expenCalendarWidget->selectedDate());
}

/**
 * @brief Opens the budget dialog.
 */
void MainWindow::loadBudget()const{
    // Refresh budget at screen
    ui->totalExpenButton->setText(QString::number(sumExpense())+"€");
    ui->totalBudgetButton->setText(QString::number(exptrc.getBudget())+"€");
}

/**
 * @brief Displays a dialog for budget details and handles budget operations.
 */
void MainWindow::detailBudget(){
    // Display window
    BudgetDialog budgetDialog(this, sumExpense(), 0.0);
    budgetDialog.exec();
    // Refresh budget at screen
    loadBudget();
}

/**
 * @brief Slot for handling the "Total Expenses" button click.
 * Calls the detailBudget() method to show the total expenses.
 */
void MainWindow::on_totalExpenButton_clicked()
{
    detailBudget();
}

/**
 * @brief Opens the budget dialog.
 */
void MainWindow::on_totalBudgetButton_clicked()
{
    detailBudget();
}

/**
 * @brief Slot for handling the activation of the 'Charts' action.
 */
void MainWindow::on_chartsAction_triggered()
{
    ChartsDialog dialog(this, getDateType(), ui->expenCalendarWidget->selectedDate());
    dialog.exec();
}

/**
 * @brief Slot for handling the activation of the 'Export to CSV' action.
 */
void MainWindow::on_csvExportAction_triggered()
{
    QString path = QFileDialog::getSaveFileName(0,tr("Sélection où enregistrer le fichier"),"./","Fichiers CSV (*.csv);;Tous les fichier (*)");
    if(!path.isEmpty()){
        if(!path.endsWith(".csv"))
            path.append(".csv");
        exptrc.exportToCSV(path);
    }
}

/**
 * @brief Checks for expired reminders and prompts the user with options.
 */
void MainWindow::checkExpired(){
    QMap<int, Reminder> expiredRem = exptrc.getReminders(true);
    for (QMap<int, Reminder>::iterator it = expiredRem.begin(); it != expiredRem.end(); ++it){
        QMessageBox alert;
        alert.setWindowTitle(tr("Rappel"));
        alert.setText(tr("Rappel: ") + it.value().getName() + '\n' + tr("Date: ") + QLocale().toString(it.value().getDate(), "dd/MM/yyyy") + "\n\n" + tr("Souhaitez-vous ajouter la dépense ?"));
        alert.addButton(tr("Ignorer"),QMessageBox::YesRole);
        alert.addButton(tr("Ajouter"),QMessageBox::ApplyRole);
        alert.addButton(tr("Effacer le rappel"),QMessageBox::DestructiveRole);

        switch(alert.exec()){
        case 1: on_expenAddButton_clicked();
            [[fallthrough]];
        case 2: exptrc.removeReminder(it.key());
            break;
        default: break;
        }
    }
}

/**
 * @brief Slot for handling the return key press event in the search line edit.
 */
void MainWindow::on_searchLineEdit_returnPressed()
{
    display();
}

/**
 * @brief Slot for handling the click event on the search button.
 */
void MainWindow::on_searchButton_clicked()
{
    display();
}

/**
 * @brief Slot for handling the triggering of the 'Modifier' action.
 */
void MainWindow::on_actionModifier_triggered()
{
    AccountDialog(exptrc).exec();
}
