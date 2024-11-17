#include "client.h"
#include "ui_client.h"
#include <QMessageBox>
#include <QDate>
#include "clientc.h"
#include <QTableView>
#include <QPrinter>
#include <QPainter>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QFileDialog>
#include <QVBoxLayout>
#include<QSslSocket>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
client::client(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::client)
{
    ui->setupUi(this);

}

client::~client()
{
    delete ui;
}


void client::on_pushButton_ajouter_clicked()
{
    // Récupération des valeurs saisies dans les champs de l'interface
    QString client_id = ui->lineEdit_id->text();
    QString nom = ui->lineEdit_nom->text();
    QString email = ui->lineEdit_email->text();
    QDate dateNaiss = ui->dateEdit->date();
    QString tel = ui->lineEdit_tel->text();
    QString sexe = ui->lineEdit_sexe->text().toUpper(); // Convertit en majuscule pour assurer la cohérence

    // Création d'un objet client avec les données saisies
    clientc newClient(client_id, nom, email,  tel, sexe,dateNaiss);

    // Validation des données saisies
    if (client_id.isEmpty() || nom.isEmpty() || email.isEmpty() || tel.isEmpty() || sexe.isEmpty()) {
        QMessageBox::critical(this, "Erreur", "Veuillez remplir tous les champs.");
        return;
    }
    if (!newClient.isValidClientId(client_id)) {
        QMessageBox::critical(this, "Erreur", "L'ID du client doit être un numéro de 8 chiffres.");
        return;
    }
    if (!newClient.isValidName(nom)) {
        QMessageBox::critical(this, "Erreur", "Le nom doit contenir uniquement des lettres.");
        return;
    }
    if (!newClient.validateEmail(email)) {
        QMessageBox::critical(this, "Erreur", "Adresse email invalide.");
        return;
    }
    if (!newClient.isValidPhoneNumber(tel)) {
        QMessageBox::critical(this, "Erreur", "Le numéro de téléphone doit être composé de chiffres uniquement et avoir une longueur valide.");
        return;
    }
    if (dateNaiss >= QDate::currentDate()) {
        QMessageBox::critical(this, "Erreur", "Veuillez entrer une date de naissance valide.");
        return;
    }
    if (sexe != "F" && sexe != "M") {
        QMessageBox::critical(this, "Erreur", "Le sexe doit être 'F' pour féminin ou 'M' pour masculin.");
        return;
    }

    // Appel de la méthode pour ajouter le client dans la base de données
    if (newClient.ajouter_client()) {
        QMessageBox::information(this, "Succès", "Client ajouté avec succès.");

        // Efface les champs après l'ajout
        ui->lineEdit_id->clear();
        ui->lineEdit_nom->clear();
        ui->lineEdit_email->clear();
        ui->dateEdit->setDate(QDate::currentDate());
        ui->lineEdit_tel->clear();
        ui->lineEdit_sexe->clear();
    } else {
        QMessageBox::critical(this, "Erreur", "Erreur lors de l'ajout du client.");
    }
}

void client::on_pushButton_afficher_clicked()
{
    clientc clientInstance;
    QSqlQueryModel* model = clientInstance.afficher();

        // Assuming you have a QTableView in your UI with the object name "tableView"
        ui->tableView->setModel(model);

}


void client::on_pushButton_supprimer_clicked()
{
    // Get the client ID from the QLineEdit (assumes ui->lineEdit_id_delete is the QLineEdit for the client ID)
    QString clientId = ui->lineEdit_id_delete->text();

    // Call the supprimer_client method to attempt deleting the client
    clientc clientInstance;
    bool success = clientInstance.supprimer_client(clientId);

    // Inform the user whether the operation succeeded or failed
    if (success) {
        QMessageBox::information(nullptr, "Succès", "Client supprimé avec succès.");
    } else {
        QMessageBox::critical(nullptr, "Erreur", "Échec de la suppression du client.");
    }
}
void client::on_pushButton_update_clicked()
{
    // Collect data from UI elements
    QString clientId = ui->lineEdit_id->text();
    QString name = ui->lineEdit_nom->text();
    QString email = ui->lineEdit_email->text();
    QString tel = ui->lineEdit_tel->text();
    QString sexe = ui->lineEdit_sexe->text();

    // Collect the date from the QDateEdit widget
    QDate daten = ui->dateEdit->date();  // Get the QDate from the QDateEdit

    // Check if the clientId field is not empty
    if (clientId.isEmpty()) {
        QMessageBox::critical(this, "Erreur", "L'ID du client ne peut pas être vide.");
        return;
    }

    // Create an instance of the clientc class and set the collected data
    clientc clientToUpdate(clientId, name, email, tel, sexe, daten);

    // Call the modifier_client method to update the client in the database
    if (clientToUpdate.modifier_client()) {
        QMessageBox::information(this, "Succès", "Les informations du client ont été mises à jour avec succès.");
    } else {
        QMessageBox::critical(this, "Erreur", "Une erreur s'est produite lors de la mise à jour des informations.");
    }
}

void client::on_pushButton_search_clicked()
{
    // Retrieve the client ID from the search line edit
    QString clientId = ui->lineEdit_search->text().trimmed();

    // Check if the input is empty
    if (clientId.isEmpty()) {
        QMessageBox::information(this, "Information", "Veuillez entrer un ID de client.");
        return;
    }

    // Use the afficher_id function to get the client data for the specified ID
   clientc c;
    QSqlQueryModel *model = c.afficher_id(clientId);

    // If the model is nullptr, the search failed or no data was found
    if (model == nullptr || model->rowCount() == 0) {
        QMessageBox::information(this, "Information", "Aucun client trouvé avec cet ID.");
        return;
    }

    // Display the result in a QTableView (assuming you have a QTableView in the UI)
    ui->tableView->setModel(model);
}

void client::on_pushButton_extract_2_clicked()
{
    clientc c;
    QSqlQueryModel *model = c.affichage_trieID_croissant();

        // Check if the model is nullptr (if query failed)
        if (model == nullptr) {
            QMessageBox::critical(this, "Erreur", "Erreur lors de l'affichage des clients triés.");
            return;
        }

        // Set the model to the table view (assuming ui->tableView exists)
        ui->tableView->setModel(model);
}

void client::on_pushButton_extract_clicked()
{
    exportClientListToPDF();  // Call export function
}

void client::exportClientListToPDF()
{
    // Demander à l'utilisateur le nom du fichier pour sauvegarder le PDF
    QString fileName = QFileDialog::getSaveFileName(this, "Save PDF", "", "PDF Files (*.pdf)");
    if (fileName.isEmpty()) {
        return; // L'utilisateur a annulé la boîte de dialogue
    }

    // Créer un QSqlQueryModel pour contenir les données des clients
    QSqlQueryModel* model = new QSqlQueryModel();

    // Créer une requête pour récupérer les données des clients
    QSqlQuery query;
    query.prepare("SELECT CLIENT_ID, NAME, EMAIL, TEL, SEXE, DATEN FROM CLIENT");

    if (query.exec()) {
        model->setQuery(query);
    } else {
        delete model;  // Si la requête a échoué, supprimer le modèle
        QMessageBox::warning(this, "Error", "Failed to retrieve client data.");
        return;
    }

    if (model == nullptr || model->rowCount() == 0) {
        QMessageBox::warning(this, "No Data", "Aucun client à exporter.");
        return;
    }

    // Préparer l'imprimante PDF et les paramètres
    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPageSize(QPageSize(QPageSize::A4));
    printer.setPageOrientation(QPageLayout::Portrait); // Vous pouvez changer en Paysage si nécessaire
    printer.setOutputFileName(fileName);

    // Configurer le QPainter pour dessiner sur le PDF
    QPainter painter(&printer);
    if (!painter.isActive()) {
        QMessageBox::warning(this, "Error", "Unable to start the painter.");
        return;
    }

    // Définir la police et la couleur pour le dessin
    painter.setFont(QFont("Arial", 10));
    QColor headerColor(49, 164, 180);  // Couleur pour les en-têtes des colonnes
    QColor cellColor(230, 244, 241);   // Couleur pour les cellules du tableau

    // Positionnement du tableau et tailles
    int x = 10;
    int y = 40;
    int rowHeight = 20;
    int colWidth = 90;

    // Dessiner le titre du document
    painter.setFont(QFont("Arial", 15, QFont::Bold));
    painter.setPen(QPen(headerColor));
    painter.drawText(x, y, "Client List");
    y += 30;

    // Dessiner les en-têtes des colonnes
    painter.setFont(QFont("Arial", 10, QFont::Bold));
    painter.setBrush(QBrush(headerColor));
    painter.setPen(QPen(Qt::black));

    // Dessiner les en-têtes pour chaque colonne
    painter.drawRect(x, y, colWidth, rowHeight);
    painter.drawText(x + 5, y + 15, "Client ID");

    painter.drawRect(x + colWidth, y, colWidth, rowHeight);
    painter.drawText(x + colWidth + 5, y + 15, "Name");

    painter.drawRect(x + 2 * colWidth, y, colWidth, rowHeight);
    painter.drawText(x + 2 * colWidth + 5, y + 15, "Email");

    painter.drawRect(x + 3 * colWidth, y, colWidth, rowHeight);
    painter.drawText(x + 3 * colWidth + 5, y + 15, "Phone");

    painter.drawRect(x + 4 * colWidth, y, colWidth, rowHeight);
    painter.drawText(x + 4 * colWidth + 5, y + 15, "Sexe");

    painter.drawRect(x + 5 * colWidth, y, colWidth, rowHeight);
    painter.drawText(x + 5 * colWidth + 5, y + 15, "Birth Date");

    y += rowHeight;

    // Dessiner les lignes du tableau avec les données
    painter.setFont(QFont("Arial", 7));
    painter.setBrush(QBrush(cellColor));

    for (int row = 0; row < model->rowCount(); ++row) {
        // Dessiner chaque cellule de la ligne
        for (int col = 0; col < model->columnCount(); ++col) {
            painter.setPen(QPen(Qt::black));
            painter.drawRect(x + col * colWidth, y, colWidth, rowHeight);
            QString data = model->data(model->index(row, col)).toString();

            // Formater la date de naissance
            if (col == 5) {  // Supposons que DATEN soit la 6e colonne (index 5)
                QDate birthDate = QDate::fromString(data, "yyyy-MM-dd");
                if (birthDate.isValid()) {
                    data = birthDate.toString("dd/MM/yyyy");  // Formater comme jour/mois/année
                }
            }

            painter.drawText(x + col * colWidth + 5, y + 15, data);
        }
        y += rowHeight;  // Passer à la ligne suivante
    }

    // Terminer le processus de peinture
    painter.end();

    // Nettoyage
    delete model;

    QMessageBox::information(this, "Export Successful", "Le fichier PDF a été exporté avec succès.");
}

void client::on_pushButton_search_2_clicked()
{  clientc clientc;
    QSqlQueryModel* model = clientc.afficher();
    clientc.genererStatistiquesSexe(model);

}

void client::on_pushButton_search_4_clicked()
{
    QString serveur = "smtp.gmail.com";
           int port = 587; // Port pour SMTP avec STARTTLS

           // Informations de l'expéditeur et du destinataire
           QString expediteur = "hedichaibi76@gmail.com";
           QString destinataire = ui->lineEdit_search_2->text();

           QString subject = "Cher notre fidele client";

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
           socket.write(QByteArray().append("lzmt nqzv zavf fmic").toBase64() + "\r\n");
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
