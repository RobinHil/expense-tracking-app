#include <QListWidgetItem>

#include "showcategorydialog.h"
#include "ui_showcategorydialog.h"
#include "mainwindow.h"

/**
 * @brief Constructs a new ShowCategoryDialog object.
 * @param parent The parent widget of the ShowCategoryDialog instance.
 */
ShowCategoryDialog::ShowCategoryDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShowCategoryDialog), mw(parent)
{
    ui->setupUi(this);

    afficherCategory();
}

/**
 * @brief Destroys the ShowCategoryDialog object.
 */
ShowCategoryDialog::~ShowCategoryDialog()
{
    delete ui;
}

/**
 * @brief Displays the list of categories.
 */
void ShowCategoryDialog::afficherCategory()
{
    MainWindow* _mw=(MainWindow*)mw;
    for(const Category& c: _mw->exptrc.getCategories()){
        ui->categoryListWidget->addItem(c.getName());
        ui->categoryListWidget->item(ui->categoryListWidget->count()-1)->setBackground(c.getColor());
    }
}
