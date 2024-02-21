#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>

class Database
{
public:
    Database() = default;
    void Init(QString server_name, QString db_name, QString login, QString password);
    bool open();
    QSqlTableModel* getVehicles();
    bool insertVehicle(QString type_input, QString reg_input, QString model_input, QString owner_input, QString hours_input);
    bool updateVehicle(QString type_input, QString reg_input, QString model_input, QString owner_input, QString hours_input, QString vehicle_id);
    bool deleteVehicle(QString vehicle_id);

    QSqlTableModel *getFlights();
    bool insertFlight(QString id_input, QString datetime_input, QString way_input);
    bool updateFlight(QString id_input, QString datetime_input, QString way_input, QString old_id, QString old_datetime, QString old_way);
    bool deleteFlight(QString old_id, QString old_datetime, QString old_way);

    QSqlTableModel *getMaintenances();
    bool insertMaintenance(QString id_input, QString interval_input, QString type_input, QString volume_input);
    bool updateMaintenance(QString id_input, QString interval_input, QString type_input, QString volume_input, QString old_id, QString old_interval, QString old_type, QString old_volume);
    bool deleteMaintenance(QString old_id, QString old_interval, QString old_type, QString old_volume);

    QSqlError getLastError();
private:
    QSqlDatabase qsqldatabase;

    QSqlTableModel* vehicle_model;

    QSqlTableModel* flight_model;

    QSqlTableModel* maintenance_model;

    QString name;

    QSqlError last_error;
};

#endif // DATABASE_H
