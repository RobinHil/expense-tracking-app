#ifndef CHARTSDIALOG_H
#define CHARTSDIALOG_H

#include <QDialog>
#include <QtCharts>
#include <QChartView>
#include <QPieSeries>

namespace Ui {
class chartsDialog;
}

/**
 * @brief The ChartsDialog class represents a dialog for managing charts.
 */
class ChartsDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Constructs a ChartsDialog object.
     * @param parent The parent widget.
     * @param dateCriterion The date sorting criterion.
     * @param selectedDate The date sorting initial date.
     */
    explicit ChartsDialog(QWidget *parent =nullptr, const int& =0, const QDate& =QDate(0,0,0));

    /**
     * @brief Destructor for ChartsDialog.
     */
    ~ChartsDialog();

private:
    /**
     * @brief Qt ChartsDialog ui interface.
     */
    Ui::chartsDialog *ui;

    /**
     * @brief Categories distribution pie chart.
     */
    QChart *categoriesChart;

    /**
     * @brief Expenses amount by date line chart.
     */
    QChart *timeChart;

    /**
     * @brief Parent MainWindow.
     */
    QWidget* mw;

    /**
     * @brief Date sorting criterion.
     */
    int dateCriterion;

    /**
     * @brief Date sorting initial date.
     */
    QDate selectedDate;

    /**
     * @brief Initializes the categories chart within the dialog.
     */
    void initCategoriesChart();

    /**
     * @brief Initializes the time chart within the dialog.
     */
    void initTimeChart();
};

#endif // CHARTSDIALOG_H
