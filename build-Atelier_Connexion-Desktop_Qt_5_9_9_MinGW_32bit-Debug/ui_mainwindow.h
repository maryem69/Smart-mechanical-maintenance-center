/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QTabWidget *tabWidget;
    QWidget *tabNouvelService;
    QLabel *label_id;
    QLineEdit *lineEdit_id;
    QLabel *label_nom;
    QLineEdit *lineEdit_nom;
    QLabel *label_description;
    QLineEdit *lineEdit_description;
    QLabel *label_prix;
    QLineEdit *lineEdit_prix;
    QLabel *label_duree;
    QLineEdit *lineEdit_duree;
    QLabel *label_equipement;
    QLineEdit *lineEdit_equipement;
    QLabel *label_employee;
    QLineEdit *lineEdit_employee;
    QPushButton *pushButton_ajouter;
    QPushButton *pushButton_update;
    QWidget *tabConsulterListe;
    QTableView *tableView;
    QLineEdit *lineEdit_search;
    QPushButton *pushButton_search;
    QPushButton *pushButton_extract;
    QPushButton *pushButton_refresh;
    QWidget *tabEliminerService;
    QLabel *label_id_delete;
    QLineEdit *lineEdit_id_delete;
    QPushButton *pushButton_supprimer;
    QWidget *tabStatistics;
    QLabel *label_statisticsTitle;
    QFrame *frameCharts;
    QHBoxLayout *horizontalLayout_charts;
    QLabel *label_chart2;
    QFrame *frameSummary;
    QVBoxLayout *verticalLayout_summary;
    QLabel *label_totalServices;
    QLabel *label_totalRevenue;
    QLabel *label_averageServiceTime;
    QPushButton *pushButton_refresh1;
    QMenuBar *menuBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(600, 500);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(10, 10, 580, 450));
        tabNouvelService = new QWidget();
        tabNouvelService->setObjectName(QStringLiteral("tabNouvelService"));
        label_id = new QLabel(tabNouvelService);
        label_id->setObjectName(QStringLiteral("label_id"));
        label_id->setGeometry(QRect(50, 30, 80, 20));
        lineEdit_id = new QLineEdit(tabNouvelService);
        lineEdit_id->setObjectName(QStringLiteral("lineEdit_id"));
        lineEdit_id->setGeometry(QRect(150, 30, 150, 20));
        label_nom = new QLabel(tabNouvelService);
        label_nom->setObjectName(QStringLiteral("label_nom"));
        label_nom->setGeometry(QRect(50, 70, 80, 20));
        lineEdit_nom = new QLineEdit(tabNouvelService);
        lineEdit_nom->setObjectName(QStringLiteral("lineEdit_nom"));
        lineEdit_nom->setGeometry(QRect(150, 70, 150, 20));
        label_description = new QLabel(tabNouvelService);
        label_description->setObjectName(QStringLiteral("label_description"));
        label_description->setGeometry(QRect(50, 110, 80, 20));
        lineEdit_description = new QLineEdit(tabNouvelService);
        lineEdit_description->setObjectName(QStringLiteral("lineEdit_description"));
        lineEdit_description->setGeometry(QRect(150, 110, 150, 20));
        label_prix = new QLabel(tabNouvelService);
        label_prix->setObjectName(QStringLiteral("label_prix"));
        label_prix->setGeometry(QRect(50, 150, 80, 20));
        lineEdit_prix = new QLineEdit(tabNouvelService);
        lineEdit_prix->setObjectName(QStringLiteral("lineEdit_prix"));
        lineEdit_prix->setGeometry(QRect(150, 150, 150, 20));
        label_duree = new QLabel(tabNouvelService);
        label_duree->setObjectName(QStringLiteral("label_duree"));
        label_duree->setGeometry(QRect(50, 190, 80, 20));
        lineEdit_duree = new QLineEdit(tabNouvelService);
        lineEdit_duree->setObjectName(QStringLiteral("lineEdit_duree"));
        lineEdit_duree->setGeometry(QRect(150, 190, 150, 20));
        label_equipement = new QLabel(tabNouvelService);
        label_equipement->setObjectName(QStringLiteral("label_equipement"));
        label_equipement->setGeometry(QRect(50, 230, 80, 20));
        lineEdit_equipement = new QLineEdit(tabNouvelService);
        lineEdit_equipement->setObjectName(QStringLiteral("lineEdit_equipement"));
        lineEdit_equipement->setGeometry(QRect(150, 230, 150, 20));
        label_employee = new QLabel(tabNouvelService);
        label_employee->setObjectName(QStringLiteral("label_employee"));
        label_employee->setGeometry(QRect(50, 270, 80, 20));
        lineEdit_employee = new QLineEdit(tabNouvelService);
        lineEdit_employee->setObjectName(QStringLiteral("lineEdit_employee"));
        lineEdit_employee->setGeometry(QRect(150, 270, 150, 20));
        pushButton_ajouter = new QPushButton(tabNouvelService);
        pushButton_ajouter->setObjectName(QStringLiteral("pushButton_ajouter"));
        pushButton_ajouter->setGeometry(QRect(150, 310, 100, 30));
        pushButton_update = new QPushButton(tabNouvelService);
        pushButton_update->setObjectName(QStringLiteral("pushButton_update"));
        pushButton_update->setGeometry(QRect(270, 310, 100, 30));
        tabWidget->addTab(tabNouvelService, QString());
        tabConsulterListe = new QWidget();
        tabConsulterListe->setObjectName(QStringLiteral("tabConsulterListe"));
        tableView = new QTableView(tabConsulterListe);
        tableView->setObjectName(QStringLiteral("tableView"));
        tableView->setGeometry(QRect(10, 70, 560, 340));
        lineEdit_search = new QLineEdit(tabConsulterListe);
        lineEdit_search->setObjectName(QStringLiteral("lineEdit_search"));
        lineEdit_search->setGeometry(QRect(10, 30, 150, 30));
        pushButton_search = new QPushButton(tabConsulterListe);
        pushButton_search->setObjectName(QStringLiteral("pushButton_search"));
        pushButton_search->setGeometry(QRect(170, 30, 80, 30));
        pushButton_extract = new QPushButton(tabConsulterListe);
        pushButton_extract->setObjectName(QStringLiteral("pushButton_extract"));
        pushButton_extract->setGeometry(QRect(310, 30, 101, 30));
        pushButton_refresh = new QPushButton(tabConsulterListe);
        pushButton_refresh->setObjectName(QStringLiteral("pushButton_refresh"));
        pushButton_refresh->setGeometry(QRect(460, 30, 100, 30));
        tabWidget->addTab(tabConsulterListe, QString());
        tabEliminerService = new QWidget();
        tabEliminerService->setObjectName(QStringLiteral("tabEliminerService"));
        label_id_delete = new QLabel(tabEliminerService);
        label_id_delete->setObjectName(QStringLiteral("label_id_delete"));
        label_id_delete->setGeometry(QRect(50, 30, 80, 20));
        lineEdit_id_delete = new QLineEdit(tabEliminerService);
        lineEdit_id_delete->setObjectName(QStringLiteral("lineEdit_id_delete"));
        lineEdit_id_delete->setGeometry(QRect(150, 30, 150, 20));
        pushButton_supprimer = new QPushButton(tabEliminerService);
        pushButton_supprimer->setObjectName(QStringLiteral("pushButton_supprimer"));
        pushButton_supprimer->setGeometry(QRect(150, 70, 100, 30));
        tabWidget->addTab(tabEliminerService, QString());
        tabStatistics = new QWidget();
        tabStatistics->setObjectName(QStringLiteral("tabStatistics"));
        label_statisticsTitle = new QLabel(tabStatistics);
        label_statisticsTitle->setObjectName(QStringLiteral("label_statisticsTitle"));
        label_statisticsTitle->setGeometry(QRect(20, 20, 200, 30));
        QFont font;
        font.setPointSize(14);
        font.setBold(true);
        font.setWeight(75);
        label_statisticsTitle->setFont(font);
        frameCharts = new QFrame(tabStatistics);
        frameCharts->setObjectName(QStringLiteral("frameCharts"));
        frameCharts->setGeometry(QRect(20, 70, 760, 200));
        frameCharts->setFrameShape(QFrame::StyledPanel);
        frameCharts->setFrameShadow(QFrame::Raised);
        horizontalLayout_charts = new QHBoxLayout(frameCharts);
        horizontalLayout_charts->setSpacing(6);
        horizontalLayout_charts->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_charts->setObjectName(QStringLiteral("horizontalLayout_charts"));
        label_chart2 = new QLabel(frameCharts);
        label_chart2->setObjectName(QStringLiteral("label_chart2"));
        label_chart2->setAlignment(Qt::AlignCenter);

        horizontalLayout_charts->addWidget(label_chart2);

        frameSummary = new QFrame(tabStatistics);
        frameSummary->setObjectName(QStringLiteral("frameSummary"));
        frameSummary->setGeometry(QRect(20, 290, 760, 200));
        frameSummary->setFrameShape(QFrame::StyledPanel);
        frameSummary->setFrameShadow(QFrame::Raised);
        verticalLayout_summary = new QVBoxLayout(frameSummary);
        verticalLayout_summary->setSpacing(6);
        verticalLayout_summary->setContentsMargins(11, 11, 11, 11);
        verticalLayout_summary->setObjectName(QStringLiteral("verticalLayout_summary"));
        label_totalServices = new QLabel(frameSummary);
        label_totalServices->setObjectName(QStringLiteral("label_totalServices"));

        verticalLayout_summary->addWidget(label_totalServices);

        label_totalRevenue = new QLabel(frameSummary);
        label_totalRevenue->setObjectName(QStringLiteral("label_totalRevenue"));

        verticalLayout_summary->addWidget(label_totalRevenue);

        label_averageServiceTime = new QLabel(frameSummary);
        label_averageServiceTime->setObjectName(QStringLiteral("label_averageServiceTime"));

        verticalLayout_summary->addWidget(label_averageServiceTime);

        pushButton_refresh1 = new QPushButton(tabStatistics);
        pushButton_refresh1->setObjectName(QStringLiteral("pushButton_refresh1"));
        pushButton_refresh1->setGeometry(QRect(460, 30, 100, 30));
        tabWidget->addTab(tabStatistics, QString());
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 26));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Gestion des Services", Q_NULLPTR));
        MainWindow->setStyleSheet(QApplication::translate("MainWindow", "\n"
"     QMainWindow { background-color: #2b2b2b; }\n"
"     QWidget { background-color: #2b2b2b; color: #ffffff; }\n"
"     QTabWidget::pane { background: #3c3c3c; }\n"
"     QTabBar::tab { background-color: #3c3c3c; color: #ffffff; }\n"
"     QTabBar::tab:selected { background-color: #4d4d4d; }\n"
"     QLabel { color: #ffffff; }\n"
"     QLineEdit { background-color: #4d4d4d; color: #ffffff; border: 1px solid #6c6c6c; }\n"
"     QPushButton { background-color: #4d4d4d; color: #ffffff; border: 1px solid #6c6c6c; }\n"
"     QPushButton:hover { background-color: #5e5e5e; }\n"
"     QTableView { background-color: #3c3c3c; color: #ffffff; }\n"
"   ", Q_NULLPTR));
        label_id->setText(QApplication::translate("MainWindow", "ID", Q_NULLPTR));
        label_nom->setText(QApplication::translate("MainWindow", "Nom", Q_NULLPTR));
        label_description->setText(QApplication::translate("MainWindow", "Description", Q_NULLPTR));
        label_prix->setText(QApplication::translate("MainWindow", "Prix", Q_NULLPTR));
        label_duree->setText(QApplication::translate("MainWindow", "Dur\303\251e", Q_NULLPTR));
        label_equipement->setText(QApplication::translate("MainWindow", "\303\211quipement", Q_NULLPTR));
        label_employee->setText(QApplication::translate("MainWindow", "Employee", Q_NULLPTR));
        pushButton_ajouter->setText(QApplication::translate("MainWindow", "Ajouter", Q_NULLPTR));
        pushButton_update->setText(QApplication::translate("MainWindow", "Update", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tabNouvelService), QApplication::translate("MainWindow", "Nouvel Service", Q_NULLPTR));
        pushButton_search->setText(QApplication::translate("MainWindow", "Search", Q_NULLPTR));
        pushButton_extract->setText(QApplication::translate("MainWindow", "Extract", Q_NULLPTR));
        pushButton_refresh->setText(QApplication::translate("MainWindow", "Refresh", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tabConsulterListe), QApplication::translate("MainWindow", "Consulter la liste", Q_NULLPTR));
        label_id_delete->setText(QApplication::translate("MainWindow", "ID", Q_NULLPTR));
        pushButton_supprimer->setText(QApplication::translate("MainWindow", "Supprimer", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tabEliminerService), QApplication::translate("MainWindow", "\303\211liminer un Service", Q_NULLPTR));
        label_statisticsTitle->setText(QApplication::translate("MainWindow", "Service Statistics", Q_NULLPTR));
        label_chart2->setText(QString());
        label_totalServices->setText(QApplication::translate("MainWindow", "Total Services: 123", Q_NULLPTR));
        label_totalRevenue->setText(QApplication::translate("MainWindow", "Total Revenue: $12,345", Q_NULLPTR));
        label_averageServiceTime->setText(QApplication::translate("MainWindow", "Average Service Time: 45 mins", Q_NULLPTR));
        pushButton_refresh1->setText(QApplication::translate("MainWindow", "Refresh", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tabStatistics), QApplication::translate("MainWindow", "Statistiques", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
