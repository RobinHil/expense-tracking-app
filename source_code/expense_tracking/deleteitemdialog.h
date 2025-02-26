#ifndef DELETEITEMDIALOG_H
#define DELETEITEMDIALOG_H

#include <QDialog>
#include <QMap>
#include <QString>

#include "mainwindow.h"

namespace Ui {
class DeleteItemDialog;
}

/**
 * @brief The DeleteItemDialog class provides a dialog for deleting an item.
 */
class DeleteItemDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Constructor for DeleteItemDialog.
     * @param _parent The parent widget.
     * @param label The label for the dialog.
     * @param items The map of items to be displayed.
     * @param _deleteItem The function pointer to the delete item function.
     */
    DeleteItemDialog(QWidget *_parent, const QString& label, const QMap<int, QString>& items, void (ExpenseTracking::*_deleteItem)(const unsigned&)const);

    /**
     * @brief Destructor for DeleteItemDialog.
     */
    ~DeleteItemDialog();

private slots:
    /**
     * @brief Slot that is called when the accept button on the dialog is clicked.
     */
    void on_dialogButtonBox_accepted();

private:
    /**
     * @brief Pointer to the user interface setup for this dialog.
     */
    Ui::DeleteItemDialog *ui;

    /**
     * @brief Pointer to the parent MainWindow instance.
     */
    MainWindow* parent;

    /**
     * @brief Pointer to the delete function.
     */
    void (ExpenseTracking::*deleteItem)(const unsigned&)const;
};

#endif // DELETEITEMDIALOG_H
