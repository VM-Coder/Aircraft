#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>

#include "database.h"
#include "login.h"
#include "addvehicle.h"
#include "editvehicle.h"
#include "flight.h"
#include "maintenance.h"
#include "help.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    Login* login_window;
    AddVehicle* add_vehicle_window;
    EditVehicle* edit_vehicle_window;
    Flight* flight_window;
    Maintenance* maintenance_window;
    Help* help_window;
    Database* database;

public slots:
    void connect_slot(QString server_input, QString database_input, QString login_input, QString password_input);
    void add_slot(QString type_input, QString reg_input, QString model_input, QString owner_input, QString hours_input);
    void edit_slot(QString type_input, QString reg_input, QString model_input, QString owner_input, QString hours_input);
    void delete_slot(QString id);
    //void flight_slot();
private slots:
    void on_refresh_triggered();
    void on_add_vehicle_triggered();
    void on_tableView_clicked(const QModelIndex &index);
    void on_MainWindow_destroyed();
    void on_flight_triggered();
    void on_maintenance_triggered();
    void on_show_help_triggered();
};



#endif // MAINWINDOW_H
