#include "connection.h"
#include <QSqlTableModel>
#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>
#include <QSqlRecord>

Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;
db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("CPP_project");//inserer le nom de la source de données
db.setUserName("aymen");//inserer nom de l'utilisateur
db.setPassword("xiozzahs");//inserer mot de passe de cet utilisateur


if (db.open())
test=true;

QSqlTableModel model(nullptr, db);
model.setTable("SERVICE");
model.select();
for (int i = 0; i < model.rowCount(); ++i) {
    qDebug() << "Service Name:" << model.record(i).value("NAME").toString();
    qDebug() << "Service Price:" << model.record(i).value("PRICE").toDouble();
}





    return  test;
}
void Connection::closeConnection(){ db.close(); }
