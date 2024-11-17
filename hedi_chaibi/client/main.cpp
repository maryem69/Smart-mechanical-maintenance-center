#include "client.h"
#include "connexion.h"
#include <QApplication>
#include <QMessageBox>
#include "clientc.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    client w;
    connexion c;
    bool test = c.createconnect();

    if (test)
    {
        w.show();

        // Replacing QTextToSpeech with QMessageBox
        QMessageBox::information(nullptr, QObject::tr("Connexion réussie"),
                                 QObject::tr("Connexion avec succès à la base de données."),
                                 QMessageBox::Ok);
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Database is not Open"),
                              QObject::tr("Connection failed.\nClick cancel to exit."),
                              QMessageBox::Cancel);
    }

    return a.exec();
}
