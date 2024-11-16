#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "service.h"
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
#include <QtCharts/QPieSeries>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QDialog>
#include <QVBoxLayout>
#include <QPieSeries>
#include <QChart>
#include <QChartView>
#include <QVBoxLayout>
#include <QDialog>
#include <QMap>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <QPieSeries>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    ui->tableView->setModel(Etmp.afficher());
    ui->tableView->setSortingEnabled(true);
    ui->tableView->horizontalHeader()->setStyleSheet(
        "QHeaderView::section {"
        "    background-color: #2c3e50;"  // Dark background color (adjust as needed)
        "    color: white;"               // Text color
        "    padding: 4px;"               // Optional: space around text
        "    font-weight: bold;"          // Optional: make text bold
        "}"
    );
    this->setStyleSheet(
        "QMainWindow {"
        "    background-color: #2c3e50;"  // Dark background color (adjust as needed)
        "    color: white;"               // Optional: makes text or icons white for contrast
        "}"
    );





    connect(ui->pushButton_update, &QPushButton::clicked, this, &MainWindow::on_pushButton_update_clicked);
    connect(ui->pushButton_search, &QPushButton::clicked, this, &MainWindow::on_pushButton_search_clicked);
    connect(ui->pushButton_extract, &QPushButton::clicked, this, &MainWindow::extractToPdf);
    connect(ui->pushButton_refresh, &QPushButton::clicked, this, &MainWindow::on_pushButton_refresh_clicked);
    connect(ui->pushButton_supprimer, &QPushButton::clicked, this, &MainWindow::on_pushButton_supprimer_clicked);

    setupConsulterListe();


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

    bool test = S.ajouter(); // Appel de la fonction d'ajout

    if(test)
    {
        ui->tableView->setModel(Etmp.afficher()); // Actualiser la vue de la table
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("Ajout effectué\nClick cancel to exit."),
                                 QMessageBox::Cancel);

        // Enregistrer l'ajout dans l'historique
        addToHistory("Ajout du service", QString::number(IDM));
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                              QObject::tr("Ajout non effectué\nClick cancel to exit."),
                              QMessageBox::Cancel);
    }
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

    bool test = S.update(); // Appel de la fonction de mise à jour

    if (test)
    {
        ui->tableView->setModel(Etmp.afficher()); // Actualiser la vue de la table
        QMessageBox::information(nullptr, QObject::tr("Update Successful"),
                                 QObject::tr("The record has been updated successfully.\n"
                                             "Click OK to continue."),
                                 QMessageBox::Ok);

        // Enregistrer l'opération d'update dans l'historique
        addToHistory("Mise à jour du service", QString::number(IDM));
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

    // Mettre à jour le modèle affiché dans la vue table
    ui->tableView->setModel(Etmp.search(searchTerm));

    // Appeler addToHistory depuis MainWindow
    addToHistory("Recherche du service", searchTerm);
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

// Slot qui est appelé lorsque le bouton est cliqué
void MainWindow::on_pushButton_search_2_clicked()
{
    setupRevenueChart();  // Appel de la méthode setupRevenueChart pour afficher ou rafraîchir le graphique
}

// Méthode pour configurer et afficher le graphique en barres
void MainWindow::setupRevenueChart() {

    QMap<QString, double> revenueData = Etmp.getRevenueByService();

    // Effacer tous les widgets dans le layout avant d'ajouter le nouveau graphique
    QLayoutItem* item;
    while ((item = ui->horizontalLayout_charts->takeAt(0)) != nullptr) {
        delete item->widget();  // Supprimer le widget du layout
        delete item;  // Supprimer l'élément du layout
    }

    // Vérifier si les données sont vides
    if (revenueData.isEmpty()) {
        // Si aucune donnée, afficher un message seulement une fois
        QMessageBox::information(this, "Aucune donnée", "Aucune donnée de revenu disponible pour le graphique.");
        return;  // Retourner sans essayer d'afficher un graphique
    }

    // Créer un QBarSet pour les valeurs des revenus
    QtCharts::QBarSet *revenueSet = new QtCharts::QBarSet("Revenu");

    // Remplir QBarSet avec les données et les noms des services
    QStringList categories;
    for (auto it = revenueData.constBegin(); it != revenueData.constEnd(); ++it) {
        categories << it.key();  // Nom du service
        *revenueSet << it.value();  // Revenu
    }

    // Créer une série QBarSeries et y ajouter le QBarSet
    QtCharts::QBarSeries *series = new QtCharts::QBarSeries();
    series->append(revenueSet);

    // Créer le graphique et y ajouter la série
    QtCharts::QChart *chart = new QtCharts::QChart();
    chart->addSeries(series);
    chart->setTitle("Revenu par service");
    chart->setAnimationOptions(QtCharts::QChart::SeriesAnimations);

    // Configurer les axes X et Y
    QtCharts::QBarCategoryAxis *axisX = new QtCharts::QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QtCharts::QValueAxis *axisY = new QtCharts::QValueAxis();
    axisY->setTitleText("Revenu ($)");
    axisY->setLabelFormat("%.2f");
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    // Afficher le graphique dans un QChartView
    QtCharts::QChartView *chartView = new QtCharts::QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // Ajouter le nouveau chartView au layout
    ui->horizontalLayout_charts->addWidget(chartView);
}

void MainWindow::on_pushButton_supprimer_clicked()
{
    QString idText = ui->lineEdit_id_delete->text().trimmed(); // Correct the name to lineEdit_id_delete
    qDebug() << "Input from lineEdit_id_delete:" << idText; // Print the input for debugging

    // Check if the input is empty
    if (idText.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please enter an ID to delete.");
        return; // Exit if the input is empty
    }

    bool ok; // Variable to check if conversion was successful
    int ID = idText.toInt(&ok); // Convert to integer

    if (!ok) {
        QMessageBox::warning(this, "Input Error", "Invalid ID input.");
        return; // Exit if the input is invalid
    }

    qDebug() << "Attempting to delete IDM:" << ID;

    bool test = Etmp.supprimer(ID);

    if (test) {
        ui->tableView->setModel(Etmp.afficher());
        QMessageBox::information(nullptr, QObject::tr("OK"), QObject::tr("Suppression effectuée\nClick cancel to exit."), QMessageBox::Cancel);
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Not OK"), QObject::tr("Suppression non effectuée\nClick cancel to exit."), QMessageBox::Cancel);
    }
    addToHistory("Suppression du service", QString::number(ID));

}

void MainWindow::addToHistory(const QString &action, const QString &serviceName)
{
    // Chemin du fichier historique
    QString filePath = "C:/Users/hp/Downloads/Atelier_Connexion/Atelier_Connexion/historique_services.txt";
    QFile file(filePath);

    // Ouvrir le fichier en mode ajout
    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        qDebug() << "Erreur lors de l'ouverture du fichier historique.";
        return;
    }

    // Créer un flux texte pour écrire dans le fichier
    QTextStream out(&file);

    // Obtenir la date et l'heure actuelles
    QDateTime currentDateTime = QDateTime::currentDateTime();

    // Écrire l'action dans le fichier historique avec la date et l'heure
    out << currentDateTime.toString("yyyy-MM-dd hh:mm:ss") << " - " << action;
    if (!serviceName.isEmpty()) {
        out << " pour le service : " << serviceName;
    }
    out << "\n";

    // Fermer le fichier
    file.close();
}
void MainWindow::saveHistoryToFile()
{
    // Chemin du fichier historique
    QString filePath = "C:/Users/hp/Downloads/Atelier_Connexion/Atelier_Connexion/historique_services.txt";
    QFile file(filePath);

    // Ouvrir le fichier en mode lecture
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Erreur lors de l'ouverture du fichier historique pour lecture.";
        return;
    }

    // Lire le contenu du fichier historique
    QTextStream in(&file);
    QString content = in.readAll();

    // Afficher le contenu de l'historique dans la console ou l'UI
    qDebug() << content;

    // Fermer le fichier
    file.close();
}



void MainWindow::on_pushButton_search_3_clicked()
{
    QString filePath = "C:/Users/hp/Downloads/Atelier_Connexion/Atelier_Connexion/historique_services.txt";
    QFile file(filePath);

    // Vérifier si le fichier peut être ouvert en mode lecture
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Erreur", "Impossible d'ouvrir le fichier d'historique.");
        return;
    }

    // Lire tout le contenu du fichier historique
    QTextStream in(&file);
    QString historyContent = in.readAll();

    // Afficher le contenu dans une boîte de dialogue ou une zone de texte
    QMessageBox::information(this, "Historique des actions", historyContent);

    // Fermer le fichier
    file.close();
}
void MainWindow::on_pushButton_search_4_clicked()
{

    QString serveur = "smtp.gmail.com";
        int port = 587; // Port pour SMTP avec STARTTLS

        // Informations de l'expéditeur et du destinataire
        QString expediteur = "aymenraddedi96325@gmail.com";
        QString destinataire = ui->lineEdit_search_2->text();

        QString subject = "[URG] A propos le nouveau service associé";

        // Détails du message
         QString corps = ui->plainTextEdit->toPlainText();

        // Connexion au serveur SMTP
        QSslSocket socket;
        socket.connectToHost(serveur, port);
        if (!socket.waitForConnected()) {
            qDebug() << "Échec de connexion au serveur SMTP:" << socket.errorString();
            return;
        }

        // Attente de la réponse du serveur
        if (!socket.waitForReadyRead()) {
            qDebug() << "Délai d'attente de réponse du serveur SMTP:" << socket.errorString();
            return;
        }
        qDebug() << socket.readAll(); // Afficher la réponse initiale du serveur

        // Envoi de la commande EHLO
        socket.write("EHLO localhost\r\n");
        if (!socket.waitForBytesWritten() || !socket.waitForReadyRead()) {
            qDebug() << "Délai d'attente de réponse du serveur SMTP (EHLO):" << socket.errorString();
            return;
        }
        qDebug() << socket.readAll(); // Afficher la réponse après EHLO

        // Envoi de la commande STARTTLS
        socket.write("STARTTLS\r\n");
        if (!socket.waitForBytesWritten() || !socket.waitForReadyRead()) {
            qDebug() << "Délai d'attente de réponse du serveur SMTP (STARTTLS):" << socket.errorString();
            return;
        }
        qDebug() << socket.readAll(); // Afficher la réponse après STARTTLS

        // Démarrer le chiffrement
        socket.startClientEncryption();
        if (!socket.waitForEncrypted()) {
            qDebug() << "Échec du chiffrement:" << socket.errorString();
            return;
        }

        // Envoi de la commande AUTH LOGIN
        socket.write("AUTH LOGIN\r\n");
        if (!socket.waitForBytesWritten() || !socket.waitForReadyRead()) {
            qDebug() << "Délai d'attente de réponse du serveur SMTP (AUTH LOGIN):" << socket.errorString();
            return;
        }
        qDebug() << socket.readAll(); // Afficher la réponse après AUTH LOGIN

        // Envoi du nom d'utilisateur encodé en Base64
        socket.write(QByteArray().append(expediteur.toUtf8()).toBase64() + "\r\n");
        if (!socket.waitForBytesWritten() || !socket.waitForReadyRead()) {
            qDebug() << "Délai d'attente de réponse du serveur SMTP (Nom d'utilisateur):" << socket.errorString();
            return;
        }
        qDebug() << socket.readAll(); // Afficher la réponse après l'envoi du nom d'utilisateur

        // Envoi du mot de passe encodé en Base64
        socket.write(QByteArray().append("flxe mzjz hirc ctdo").toBase64() + "\r\n");
        if (!socket.waitForBytesWritten() || !socket.waitForReadyRead()) {
            qDebug() << "Échec de l'authentification SMTP (Mot de passe):" << socket.errorString();
            return;
        }
        qDebug() << socket.readAll(); // Afficher la réponse après l'envoi du mot de passe

        // Envoi de la commande MAIL FROM
        socket.write("MAIL FROM:<" + expediteur.toUtf8() + ">\r\n");
        if (!socket.waitForBytesWritten() || !socket.waitForReadyRead()) {
            qDebug() << "Délai d'attente de réponse du serveur SMTP (MAIL FROM):" << socket.errorString();
            return;
        }
        qDebug() << socket.readAll(); // Afficher la réponse après MAIL FROM

        // Envoi de la commande RCPT TO
        socket.write("RCPT TO:<" + destinataire.toUtf8() + ">\r\n");
        if (!socket.waitForBytesWritten() || !socket.waitForReadyRead()) {
            qDebug() << "Délai d'attente de réponse du serveur SMTP (RCPT TO):" << socket.errorString();
            return;
        }
        qDebug() << socket.readAll(); // Afficher la réponse après RCPT TO

        // Envoi de la commande DATA
        socket.write("DATA\r\n");
        if (!socket.waitForBytesWritten() || !socket.waitForReadyRead()) {
            qDebug() << "Délai d'attente de réponse du serveur SMTP (DATA):" << socket.errorString();
            return;
        }
        qDebug() << socket.readAll(); // Afficher la réponse après DATA

        // Envoi des en-têtes et du corps du message
        socket.write("From: " + expediteur.toUtf8() + "\r\n");
        socket.write("To: " + destinataire.toUtf8() + "\r\n");
        socket.write("Subject: " + subject.toUtf8() + "\r\n");
        socket.write("\r\n");
        socket.write(corps.toUtf8() + "\r\n");
        socket.write(".\r\n");
        if (!socket.waitForBytesWritten() || !socket.waitForReadyRead()) {
            qDebug() << "Échec d'envoi des données du mail:" << socket.errorString();
            return;
        }
        qDebug() << socket.readAll(); // Afficher la réponse après l'envoi des données du mail

        // Envoi de la commande QUIT
        socket.write("QUIT\r\n");
        if (!socket.waitForBytesWritten()) {
            qDebug() << "Échec d'envoi de la commande QUIT:" << socket.errorString();
            return;
        }

        // Fermeture de la connexion
        socket.close();
        QMessageBox::information(this, "Succès", "L'email a été envoyé avec succès à " + destinataire);

















}




