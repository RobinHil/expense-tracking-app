#include <QPieSlice>

#include "chartsdialog.h"
#include "ui_chartsdialog.h"
#include "mainwindow.h"

/**
 * @brief Constructor for ChartsDialog.
 * @param parent The parent widget, typically the main window.
 * @param _dateCriterion The criterion for filtering data by date.
 * @param _selectedDate The selected date for filtering the expenses.
 */
ChartsDialog::ChartsDialog(QWidget *parent, const int& _dateCriterion, const QDate& _selectedDate) :
    QDialog(parent),
    ui(new Ui::chartsDialog),
    mw(parent),
    dateCriterion(_dateCriterion),
    selectedDate(_selectedDate)
{
    ui->setupUi(this);

    if (dateCriterion == 1)
        dateCriterion = 2;

    initCategoriesChart();
    initTimeChart();

    setBaseSize(width(), height());
}

/**
 * @brief Destructor for ChartsDialog.
 */
ChartsDialog::~ChartsDialog()
{
    delete ui;
    delete categoriesChart;
    delete timeChart;
}

/**
 * @brief Initializes the categories chart.
 *        Constructs a pie chart based on categorized expenses.
 */
void ChartsDialog::initCategoriesChart()
{
    MainWindow* _mw=(MainWindow*)mw;

    QPieSeries* pieSeries = new QPieSeries();

    QVector<QPair<int,Expense>> expenses;
    double sum = 0;

    QMap<int,Category> cat = _mw->exptrc.getCategories();
    for (const int& catId : cat.keys())
    {
        expenses = _mw->exptrc.getExpenses(catId, "", dateCriterion, selectedDate);
        if (expenses.size() != 0)
        {
            sum = 0;
            for (const QPair<int,Expense>& p : expenses)
                sum += p.second.getValue();

            QPieSlice *slice = new QPieSlice(cat.value(catId).getName(), sum);
            pieSeries->append(slice);
            slice->setColor(cat.value(catId).getColor());
        }
    }

    expenses = _mw->exptrc.getExpenses(0, "", dateCriterion, selectedDate);
    if (expenses.size() != 0)
    {
        sum = 0;
        for (const QPair<int,Expense>& p : expenses)
            sum += p.second.getValue();

        QPieSlice *slice = new QPieSlice(tr("Sans catégorie"), sum);
        pieSeries->append(slice);
    }

    for (QPieSlice *slice : pieSeries->slices())
        slice->setLabel(slice->label()+" - "+QString("%1%").arg(100*slice->percentage(), 0, 'f', 1));

    categoriesChart = new QChart();
    categoriesChart->addSeries(pieSeries);
    categoriesChart->setTitle(tr("Répartition des catégories parmi les dépenses"));
    categoriesChart->legend()->setAlignment(Qt::AlignLeft);
    categoriesChart->legend()->setMarkerShape(QLegend::MarkerShapeCircle);

    QChartView *chartView = new QChartView(categoriesChart);
    chartView->setParent(ui->categoriesChartFrame);
    chartView->setRenderHint(QPainter::Antialiasing);
}

/**
 * @brief Initializes the time chart.
 *        Constructs a line chart based on expenses amount by date.
 */
void ChartsDialog::initTimeChart()
{
    MainWindow* _mw=(MainWindow*)mw;

    QLineSeries* lineSeries = new QLineSeries();

    QDate date;
    double maxValue = 0;
    double sum = 0;
    if (dateCriterion == 2)
    {

        for (date.setDate(selectedDate.year(), selectedDate.month(), 1); date.day()<date.daysInMonth(); date.setDate(date.year(), date.month(), date.day()+1))
        {
            sum = _mw->exptrc.getExpensesSum(dateCriterion-1, date);
            if (sum>maxValue)
                maxValue = sum;
            lineSeries->append(QDateTime::fromString(date.toString("dd/MM/yyyy"), "dd/MM/yyyy").toMSecsSinceEpoch(), sum);
        }
        date.setDate(date.year(), date.month(), date.daysInMonth());
        sum = _mw->exptrc.getExpensesSum(dateCriterion-1, date);
        if (sum>maxValue)
            maxValue = sum;
        lineSeries->append(QDateTime::fromString(date.toString("dd/MM/yyyy"), "dd/MM/yyyy").toMSecsSinceEpoch(), sum);
    }
    else if (dateCriterion == 3)
    {
        for (date.setDate(selectedDate.year(), 1, 15); date.month()<12; date.setDate(date.year(), date.month()+1, 15))
        {
            sum = _mw->exptrc.getExpensesSum(dateCriterion-1, date);
            if (sum>maxValue)
                maxValue = sum;
            lineSeries->append(QDateTime::fromString(date.toString("dd/MM/yyyy"), "dd/MM/yyyy").toMSecsSinceEpoch(), sum);
        }
        date.setDate(date.year(), 12, 15);
        sum = _mw->exptrc.getExpensesSum(dateCriterion-1, date);
        if (sum>maxValue)
            maxValue = sum;
        lineSeries->append(QDateTime::fromString(date.toString("dd/MM/yyyy"), "dd/MM/yyyy").toMSecsSinceEpoch(), sum);
    }

    timeChart = new QChart();
    timeChart->addSeries(lineSeries);
    timeChart->legend()->hide();
    timeChart->setTitle(tr("Évolution des dépenses au cours de la période sélectionnée"));

    QDateTimeAxis* axisX = new QDateTimeAxis();
    if (dateCriterion == 2) {
        axisX->setTickCount(selectedDate.daysInMonth()/2);
        axisX->setFormat("dd");
        axisX->setTitleText(QString(QLocale::system().monthName(selectedDate.month())+" "+selectedDate.toString("yyyy")).toStdString().c_str());
    } else if (dateCriterion == 3) {
        axisX->setTickCount(12);
        axisX->setFormat("MMM");
        axisX->setTitleText(QString(selectedDate.toString("yyyy")).toStdString().c_str());
    }
    timeChart->addAxis(axisX, Qt::AlignBottom);
    lineSeries->attachAxis(axisX);

    QValueAxis* axisY = new QValueAxis();
    axisY->setLabelFormat("%i");
    axisY->setTitleText(tr("Montant total des dépenses (€)"));
    axisY->setRange(0, maxValue+maxValue/10);
    lineSeries->setPointsVisible(true);
    timeChart->addAxis(axisY, Qt::AlignLeft);
    lineSeries->attachAxis(axisY);

    QChartView* chartView = new QChartView(timeChart);
    chartView->setParent(ui->timeChartFrame);
    chartView->setRenderHint(QPainter::Antialiasing);
}
