#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>

#include "expensetracking.h"

/**
 * @brief This macro opens the Qt namespace to prevent naming conflicts with other libraries.
 */
QT_BEGIN_NAMESPACE
/**
 * @brief The Ui namespace contains user interface-related classes generated by Qt's User Interface Compiler (uic).
 */
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/**
 * @brief The MainWindow class is the main interface of the application.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /// @brief Instance of ExpenseTracking used by the application.
    ExpenseTracking exptrc;

    /**
     * @brief Constructor for MainWindow.
     * @param parent The parent widget, nullptr by default.
     */
    MainWindow(const QString&, QWidget *parent = nullptr);

    /**
     * @brief Destructor for MainWindow.
     */
    ~MainWindow();

    /**
     * @brief Calculates and returns the sum of expenses.
     * @return Total sum of expenses.
     */
    double sumExpense()const;

    /**
     * @brief Retrieves the date type.
     * @return The date type.
     */
    int getDateType() const;

    /**
     * @brief Loads the budget information.
     */
    void loadBudget()const;

    /**
     * @brief Displays main window contents.
     */
    void display()const;

    /**
     * @brief Provides detailed budget information.
     */
    void detailBudget();

    /**
     * @brief Displays categories in the main window.
     */
    void displayCategory()const;

    /**
     * @brief Checks for any expired reminders.
     */
    void checkExpired();

private slots:

    // Slot methods for various UI actions
    /**
     * @brief Slot for handling the "Add Expense" button click.
     */
    void on_expenAddButton_clicked();

    /**
     * @brief Slot for handling the "Delete Expense" button click.
     */
    void on_expenDeleteButton_clicked();

    /**
     * @brief Slot for handling the "About" action triggered (e.g., in the menu).
     */
    void on_aboutAction_triggered();

    /**
     * @brief Slot for handling the "Exit" action triggered (e.g., in the menu).
     */
    void on_exitAction_triggered();

    /**
     * @brief Slot for handling the "Use" action triggered (e.g., in the menu).
     */
    void on_useAction_triggered();

    /**
     * @brief Slot for handling the "Contact" action triggered (e.g., in the menu).
     */
    void on_contactAction_triggered();

    /**
     * @brief Slot for handling the "Show Categories" action triggered (e.g., in the menu).
     */
    void on_showCatAction_triggered();

    /**
     * @brief Slot for handling changes in the category choice combo box.
     * @param index The index of the selected item.
     */
    void on_categoryChoiceComboBox_currentIndexChanged(int index);

    /**
     * @brief Slot for handling the "Add Category" action triggered (e.g., in the menu).
     */
    void on_addCatAction_triggered();

    /**
     * @brief Slot for handling the "Delete Category" action triggered (e.g., in the menu).
     */
    void on_deleteCatAction_triggered();

    /**
     * @brief Slot for handling the "Day" radio button click.
     */
    void on_dayRadioButton_clicked();

    /**
     * @brief Slot for handling changes in the calendar widget selection.
     */
    void on_expenCalendarWidget_selectionChanged();

    /**
     * @brief Slot for handling the "Month" radio button click.
     */
    void on_monthRadioButton_clicked();

    /**
     * @brief Slot for handling the "Year" radio button click.
     */
    void on_yearRadioButton_clicked();

    /**
     * @brief Slot for handling double clicks on the expense table.
     * @param row The row index of the double-clicked cell.
     */
    void on_expenTableWidget_cellDoubleClicked(int row);

    /**
     * @brief Slot for handling the "Add Reminder" action triggered (e.g., in the menu).
     */
    void on_addRemAction_triggered();

    /**
     * @brief Slot for handling the "Delete Reminder" action triggered (e.g., in the menu).
     */
    void on_delRemAction_triggered();

    /**
     * @brief Slot for handling the "Show Reminders" action triggered (e.g., in the menu).
     */
    void on_showRemAction_triggered();

    /**
     * @brief Slot for handling the "Charts" action triggered (e.g., in the menu).
     */
    void on_chartsAction_triggered();

    /**
     * @brief Slot for handling the "CSV Export" action triggered (e.g., in the menu).
     */
    void on_csvExportAction_triggered();

    /**
     * @brief Slot for handling the "Total Expenses" button click.
     */
    void on_totalExpenButton_clicked();

    /**
     * @brief Slot for handling the "Total Budget" button click.
     */
    void on_totalBudgetButton_clicked();

    /**
     * @brief Slot for handling the return key press in the search line edit.
     */
    void on_searchLineEdit_returnPressed();

    /**
     * @brief Slot for handling the "Search" button click.
     */
    void on_searchButton_clicked();

    /**
     * @brief Slot for handling the "Modifier" action triggered (e.g., in the menu).
     */
    void on_actionModifier_triggered();

private:
    Ui::MainWindow *ui;

    /**
     * @brief Sets an item in a table.
     * @param row The row of the table.
     * @param col The column of the table.
     * @param s The string to set in the table cell.
     */
    void setItem(int row, int col, const QString& s) const;

    /**
     * @brief Retrieves the row ID from a table.
     * @param row The row of the table.
     * @return The ID of the row.
     */
    int getRowId(int row) const;
};

#endif // MAINWINDOW_H
