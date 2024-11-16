#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "service.h"
#include <QSqlQuery>
#include <QStandardItemModel>
#include <QHeaderView>
#include <QTableView>
#include <QSqlTableModel>
#include <QtCharts/QPieSeries>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setupConsulterListe();
    void setupRevenueChart();

private slots:
    void on_pushButton_ajouter_clicked();
    void on_pushButton_supprimer_clicked();
    void on_pushButton_update_clicked();
    void on_pushButton_search_clicked();
    void extractToPdf();
    void on_pushButton_refresh_clicked();

    void on_pushButton_search_2_clicked();
    void addToHistory(const QString &action, const QString &serviceName = "");  // Ajouter une action à l'historique
      void saveHistoryToFile();  // Sauvegarder l'historique dans un fichier

      void on_pushButton_search_3_clicked();

      void on_pushButton_search_4_clicked();

private:
    Ui::MainWindow *ui;
     QTableView *tableView;
    Service Etmp;

};

#endif // MAINWINDOW_H
