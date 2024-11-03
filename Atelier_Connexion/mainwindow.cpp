#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QPrinter>
#include <QPainter>
#include <QTextDocument>
#include <QFileDialog>
#include <QtCharts/QPieSeries>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QDebug>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView->setModel(Etmp.afficher());
    ui->tableView->setSortingEnabled(true);
    ui->tableView->horizontalHeader()->setStyleSheet("QHeaderView::section { background-color: white; color: black; }");

    connect(ui->pushButton_update, &QPushButton::clicked, this, &MainWindow::on_pushButton_update_clicked);
    connect(ui->pushButton_search, &QPushButton::clicked, this, &MainWindow::on_pushButton_search_clicked);
    connect(ui->pushButton_extract, &QPushButton::clicked, this, &MainWindow::extractToPdf);
    connect(ui->pushButton_refresh, &QPushButton::clicked, this, &MainWindow::on_pushButton_refresh_clicked);
    connect(ui->pushButton_supprimer, &QPushButton::clicked, this, &MainWindow::on_pushButton_supprimer_clicked);

    setupConsulterListe();
    setupRevenueChart();

    ui->lineEdit_id->setValidator(new QIntValidator(1, 1000000, this));
    QDoubleValidator *doubleValidator = new QDoubleValidator(0, 1000000, 2, this);
    doubleValidator->setNotation(QDoubleValidator::StandardNotation);
    ui->lineEdit_prix->setValidator(doubleValidator);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_pushButton_ajouter_clicked()
{
    int IDM = ui->lineEdit_id->text().toInt();
    QString NAME = ui->lineEdit_nom->text();
    QString DESCRIPTION = ui->lineEdit_description->text();
    float PRICE = ui->lineEdit_prix->text().toFloat();
    QString DURATION = ui->lineEdit_duree->text();
    QString EQUIPEMENT = ui->lineEdit_equipement->text();
    QString EMPLOYEE = ui->lineEdit_employee->text();

    if(IDM <= 0 || NAME.isEmpty() || PRICE < 0.0f || DURATION.isEmpty()) {
            QMessageBox::warning(this, "Input Error", "Please fill in all required fields.");
            return;
        }

    Service S(IDM, NAME, DESCRIPTION, DURATION, EMPLOYEE, EQUIPEMENT, PRICE);

    bool test = S.ajouter();

    if(test)
    {
        ui->tableView->setModel(Etmp.afficher());
        QMessageBox::information(nullptr, QObject::tr("OK"), QObject::tr("Ajout effectué\nClick cancel to exit."), QMessageBox::Cancel);
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Not OK"), QObject::tr("Ajout non effectué\nClick cancel to exit."), QMessageBox::Cancel);
    }
}

void MainWindow::on_pushButton_supprimer_clicked()
{
    int ID;
    ID=ui->lineEdit_id->text().toInt();
    qDebug() << "Attempting to delete IDM:" << ID;
    bool test;
    test=Etmp.supprimer(ID);

    if(test)
    {
        ui->tableView->setModel(Etmp.afficher());
        QMessageBox::information(nullptr, QObject::tr("OK"),QObject::tr("Suppresion effectué\n""click cancel to exit."), QMessageBox::Cancel);
    }else
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),QObject::tr("Suppresion non effectué\n""click cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_pushButton_update_clicked()
{
    int IDM = ui->lineEdit_id->text().toInt();
    QString NAME = ui->lineEdit_nom->text();
    QString DESCRIPTION = ui->lineEdit_description->text();
    float PRICE = ui->lineEdit_prix->text().toFloat();
    QString DURATION = ui->lineEdit_duree->text();
    QString EQUIPEMENT = ui->lineEdit_equipement->text();
    QString EMPLOYEE = ui->lineEdit_employee->text();

    if(IDM <= 0 || NAME.isEmpty() || PRICE < 0.0f || DURATION.isEmpty()) {
            QMessageBox::warning(this, "Input Error", "Please fill in all required fields.");
            return;
        }

    Service S(IDM, NAME, DESCRIPTION, DURATION, EMPLOYEE, EQUIPEMENT, PRICE);

    bool test = S.update(); // Call the update function

    if (test)
    {
        ui->tableView->setModel(Etmp.afficher()); // Refresh table view
        QMessageBox::information(nullptr, QObject::tr("Update Successful"),
                                 QObject::tr("The record has been updated successfully.\n"
                                             "Click OK to continue."),
                                 QMessageBox::Ok);
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Update Failed"),
                              QObject::tr("The update operation failed.\n"
                                          "Click Cancel to exit."),
                              QMessageBox::Cancel);
    }
}

void MainWindow::on_pushButton_search_clicked() {
    QString searchTerm = ui->lineEdit_search->text();
    if (searchTerm.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please enter a search term.");
        return;
    }

    // Update the model displayed in the table view
    ui->tableView->setModel(Etmp.search(searchTerm));
}

void MainWindow::extractToPdf() {
    QString filePath = QFileDialog::getSaveFileName(this, "Save PDF", "", "*.pdf");
    if (filePath.isEmpty()) return;

    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(filePath);

    QPainter painter(&printer);

    int rowHeight = 500;
    int xOffset = 50;
    int yOffset = 100;
    int pageWidth = printer.pageRect().width();

    // Assuming you want to print all columns in the table
    int numColumns = ui->tableView->model()->columnCount();
    int numRows = ui->tableView->model()->rowCount();
    int columnWidth = pageWidth / numColumns;

    // Print headers
    for (int col = 0; col < numColumns; ++col) {
        QString header = ui->tableView->model()->headerData(col, Qt::Horizontal).toString();
        painter.drawText(xOffset + col * columnWidth, yOffset, header);
    }

    // Print data rows
    yOffset += rowHeight;
    for (int row = 0; row < numRows; ++row) {
        for (int col = 0; col < numColumns; ++col) {
            QModelIndex index = ui->tableView->model()->index(row, col);
            QString data = index.data().toString();
            painter.drawText(xOffset + col * columnWidth, yOffset + row * rowHeight, data);
        }
    }

    painter.end();
    QMessageBox::information(this, "Export to PDF", "The list has been successfully exported as a PDF.");
}

void MainWindow::on_pushButton_refresh_clicked() {
    ui->tableView->setModel(Etmp.afficher());

}

void MainWindow::setupConsulterListe()
{
    // Create and set the SQL model
    QSqlTableModel *model = new QSqlTableModel(this);
    model->setTable("SERVICE");  // Replace "SERVICE" with your actual table name
    model->select();  // Load data

    // Enable sorting for the model
    model->setSort(0, Qt::AscendingOrder);  // Sort by the first column by default

    // Set the model to the tableView
    ui->tableView->setModel(model);
    ui->tableView->setSortingEnabled(true);  // Enable sorting in the UI
}

void MainWindow::setupRevenueChart() {
    // Fetch revenue data
    QMap<QString, double> revenueData = Etmp.getRevenueByService();

    // Create a QBarSet for revenue values
    QtCharts::QBarSet *revenueSet = new QtCharts::QBarSet("Revenue");

    // Fill QBarSet with revenue data and category names
    QStringList categories;
    for (auto it = revenueData.constBegin(); it != revenueData.constEnd(); ++it) {
        categories << it.key();  // Service name
        *revenueSet << it.value();  // Revenue
    }

    // Create QBarSeries and add the set to it
    QtCharts::QBarSeries *series = new QtCharts::QBarSeries();
    series->append(revenueSet);

    // Create the chart and set the series
    QtCharts::QChart *chart = new QtCharts::QChart();
    chart->addSeries(series);
    chart->setTitle("Revenue by Service");
    chart->setAnimationOptions(QtCharts::QChart::SeriesAnimations);

    // Setup X and Y axes
    QtCharts::QBarCategoryAxis *axisX = new QtCharts::QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QtCharts::QValueAxis *axisY = new QtCharts::QValueAxis();
    axisY->setTitleText("Revenue ($)");
    axisY->setLabelFormat("%.2f");
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    // Display the chart in a QChartView
    QtCharts::QChartView *chartView = new QtCharts::QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // Add chartView to the layout in your UI
    ui->horizontalLayout_charts->addWidget(chartView);
}



