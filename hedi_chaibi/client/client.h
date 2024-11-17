#ifndef CLIENT_H
#define CLIENT_H
#include <QSqlQueryModel>

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class client; }
QT_END_NAMESPACE

class client : public QWidget
{
    Q_OBJECT

public:
    client(QWidget *parent = nullptr);
    ~client();

private slots:
    void on_pushButton_ajouter_clicked();

    void on_pushButton_afficher_clicked();

    void on_pushButton_supprimer_clicked();

    void on_pushButton_update_clicked();

    void on_pushButton_search_clicked();

    void on_pushButton_extract_2_clicked();

    void on_pushButton_extract_clicked();
    void exportClientListToPDF();


    void on_pushButton_search_2_clicked();

    void on_pushButton_search_4_clicked();

private:
    Ui::client *ui;
};
#endif // CLIENT_H
