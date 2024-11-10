#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "voiture.h"
#include <QMessageBox>
#include <QtCharts>
#include <QSqlQuery>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_ajouterButton_clicked()
{
    QString MATRICULE=ui->matriculeInput->text();
    QString MARQUE=ui->marqueInput->text();
    QString MODELE=ui->modeleInput->text();
    QString KILOMETRAGE=ui->kilometrageInput->text();
    QString DATE_ARRIVAGE=ui->dateArrivageInput->date().toString();
    QString DATE_SORTIE=ui->dateSortieInput->date().toString();
    QString TYPE_DE_PANNE=ui->tt->text();
    QRegularExpression matriculeRegex(R"(^\d{4} [A-Z]{3} \d{3}$)");

    voiture v(MATRICULE,MARQUE,MODELE,KILOMETRAGE,DATE_ARRIVAGE,DATE_SORTIE,TYPE_DE_PANNE);
    if(MATRICULE =="" || MARQUE =="" || MODELE =="" || KILOMETRAGE =="" || DATE_ARRIVAGE =="" || DATE_SORTIE =="" || TYPE_DE_PANNE =="" )
    {
        QMessageBox::critical(nullptr, QObject::tr("erreur"),
                    QObject::tr("veuillez remplir les champs\n"), QMessageBox::Cancel);
    }
    else{
        if(TYPE_DE_PANNE!="mecanique" && TYPE_DE_PANNE!="electrique" && TYPE_DE_PANNE!="vidange" && TYPE_DE_PANNE!="autre" ){
            QMessageBox::critical(nullptr, QObject::tr("erreur"),
                        QObject::tr("le type doit etre mecanique ou electrique ou vidange ou autre"), QMessageBox::Cancel);
        }
        else{
            if(!matriculeRegex.match(MATRICULE).hasMatch())
            {
                QMessageBox::critical(nullptr, QObject::tr("erreur"),
                            QObject::tr("la matricule doit etre comme ca xxxx TUN xxx"), QMessageBox::Cancel);
            }
            else{
                if(KILOMETRAGE.contains(QRegExp("[^0-9]")))
                {
                    QMessageBox::critical(nullptr, QObject::tr("erreur"),
                                QObject::tr("le kilometrage doit contient que de nombre"), QMessageBox::Cancel);
                }
                else{
        v.ajouter();
        ui->tableView->setModel(v.afficher());
                }
            }
        }
    }

}

void MainWindow::on_supprimerButton_clicked()
{
    QString MATRICULE=ui->matriculeInput->text();
    voiture v;
    v.supprimer(MATRICULE);
    ui->tableView->setModel(v.afficher());
}

void MainWindow::on_modifierButton_clicked()
{
    QString MATRICULE=ui->matriculeInput->text();
    QString MARQUE=ui->marqueInput->text();
    QString MODELE=ui->modeleInput->text();
    QString KILOMETRAGE=ui->kilometrageInput->text();
    QString DATE_ARRIVAGE=ui->dateArrivageInput->date().toString();
    QString DATE_SORTIE=ui->dateSortieInput->date().toString();
    QString TYPE_DE_PANNE=ui->tt->text();
    voiture v(MATRICULE,MARQUE,MODELE,KILOMETRAGE,DATE_ARRIVAGE,DATE_SORTIE,TYPE_DE_PANNE);
    v.modifier();
    ui->tableView->setModel(v.afficher());
}



void MainWindow::on_pushButton_clicked()
{
     voiture v;
    ui->tableView->setModel(v.tri());
}

void MainWindow::on_matriculeInput_3_textChanged(const QString &arg1)
{
    voiture v;
    ui->tableView->setModel(v.rechercher(arg1));
}

void MainWindow::on_pushButton_2_clicked()
{
        QSqlQuery query;
        query.exec("SELECT TYPE_DE_PANNE, COUNT(*) FROM VOITURE GROUP BY TYPE_DE_PANNE");

        QtCharts::QPieSeries *series = new QtCharts::QPieSeries();
        while (query.next()) {
            QString type = query.value(0).toString();
            int count = query.value(1).toInt();
            QtCharts::QPieSlice *slice = new QtCharts::QPieSlice(type, count);
            series->append(slice);
        }

        QtCharts::QChart *chart = new QtCharts::QChart();
        chart->addSeries(series);
        chart->setTitle("Statistics based on VOITURE type_de_panne");
        chart->setAnimationOptions(QtCharts::QChart::SeriesAnimations);

        QtCharts::QChartView *chartView = new QtCharts::QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);
        chartView->setParent(ui->tableView_2);
        chartView->resize(ui->tableView_2->size());
        chartView->show();


}
