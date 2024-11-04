#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::clearInputs() {
    ui->matriculeInput->clear();
    ui->marqueInput->clear();
    ui->modeleInput->clear();
    ui->kilometrageInput->clear();
    ui->dateArrivageInput->clear();
    ui->dateSortieInput->clear();
    ui->typePanneInput->clear();
    ui->idProprietaireInput->clear();
}

void MainWindow::on_ajouterButton_clicked() {
    QMap<QString, QString> newRecord;
    newRecord["matricule"] = ui->matriculeInput->text();
    newRecord["marque"] = ui->marqueInput->text();
    newRecord["modele"] = ui->modeleInput->text();
    newRecord["kilometrage"] = ui->kilometrageInput->text();
    newRecord["date_arrivage"] = ui->dateArrivageInput->text();
    newRecord["date_sortie"] = ui->dateSortieInput->text();
    newRecord["type_panne"] = ui->typePanneInput->text();
    newRecord["id_proprietaire"] = ui->idProprietaireInput->text();

    records.append(newRecord);
    QMessageBox::information(this, "Success", "Record added!");
    clearInputs();
}

void MainWindow::on_modifierButton_clicked() {
    QString matricule = ui->matriculeInput->text();
    for (auto &record : records) {
        if (record["matricule"] == matricule) {
            record["marque"] = ui->marqueInput->text();
            record["modele"] = ui->modeleInput->text();
            record["kilometrage"] = ui->kilometrageInput->text();
            record["date_arrivage"] = ui->dateArrivageInput->text();
            record["date_sortie"] = ui->dateSortieInput->text();
            record["type_panne"] = ui->typePanneInput->text();
            record["id_proprietaire"] = ui->idProprietaireInput->text();
            QMessageBox::information(this, "Success", "Record modified!");
            clearInputs();
            return;
        }
    }
    QMessageBox::warning(this, "Error", "Record not found!");
}

void MainWindow::on_supprimerButton_clicked() {
    QString matricule = ui->matriculeInput->text();
    for (int i = 0; i < records.size(); ++i) {
        if (records[i]["matricule"] == matricule) {
            records.removeAt(i);
            QMessageBox::information(this, "Success", "Record deleted!");
            clearInputs();
            return;
        }
    }
    QMessageBox::warning(this, "Error", "Record not found!");
}
