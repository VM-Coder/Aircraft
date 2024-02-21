#include "database.h"
#include <QDebug>
#include <QSqlError>

void Database::Init(QString server_name, QString db_name, QString login, QString password)
{
    qsqldatabase = QSqlDatabase::addDatabase("QODBC");
    qsqldatabase.setDatabaseName("DRIVER={SQL Server};SERVER=" + server_name + ";DATABASE=" + db_name);
    qsqldatabase.setUserName(login);
    qsqldatabase.setPassword(password);

    name = db_name;
}

bool Database::open()
{
    if (qsqldatabase.open()){
        return true;
    } else {
        last_error = qsqldatabase.lastError();
        return false;
    }
}

QSqlTableModel* Database::getVehicles()
{
    if (vehicle_model)
        delete vehicle_model;
    vehicle_model = new QSqlTableModel;
    vehicle_model->setTable("vehicle");
    vehicle_model->select();

    vehicle_model->setHeaderData(0, Qt::Horizontal, "id");
    vehicle_model->setHeaderData(1, Qt::Horizontal, "Тип");
    vehicle_model->setHeaderData(2, Qt::Horizontal, "Регистрационный номер");
    vehicle_model->setHeaderData(3, Qt::Horizontal, "Модель");
    vehicle_model->setHeaderData(4, Qt::Horizontal, "Владелец");
    vehicle_model->setHeaderData(5, Qt::Horizontal, "Отработанные моточасы");

    return vehicle_model;
}

bool Database::insertVehicle(QString type_input, QString reg_input, QString model_input, QString owner_input, QString hours_input)
{
    QSqlQuery query;
    query.prepare("INSERT INTO [" + name + "].[dbo].[vehicle] VALUES ((SELECT ISNULL(MAX(id)+1, 1) FROM [" + name + "].[dbo].[vehicle]), '" +
                type_input + "', '" +
                reg_input + "', '" +
                model_input + "', '" +
                owner_input + "', " +
                hours_input + ")");

    if (query.exec()){
        return true;
    } else {
        last_error = query.lastError();
        return false;
    }
}

bool Database::updateVehicle(QString type_input, QString reg_input, QString model_input, QString owner_input, QString hours_input, QString vehicle_id)
{
    QSqlQuery query;
    query.prepare("UPDATE [" + name + "].[dbo].[vehicle] SET [type]='" +
                  type_input + "', [reg_number]='" +
                  reg_input + "', [model]='" +
                  model_input + "', [owner]='" +
                  owner_input + "', [engine_hours]=" +
                  hours_input + " WHERE id=" + vehicle_id);

    if (query.exec()){
        return true;
    } else {
        last_error = query.lastError();
        return false;
    }
}

bool Database::deleteVehicle(QString vehicle_id)
{
    qsqldatabase.transaction();
    QSqlQuery query;

    query.prepare("DELETE FROM [" + name + "].[dbo].[flight] WHERE vehicle_id=" + vehicle_id);
    query.exec();

    query.prepare("DELETE FROM [" + name + "].[dbo].[maintenance] WHERE vehicle_id=" + vehicle_id);
    query.exec();

    query.prepare("DELETE FROM [" + name + "].[dbo].[vehicle] WHERE id=" + vehicle_id);
    query.exec();

    if (qsqldatabase.commit()){
        return true;
    } else {
        last_error = qsqldatabase.lastError();
        return false;
    }
}

QSqlTableModel *Database::getFlights()
{
    if (flight_model)
        delete flight_model;
    flight_model = new QSqlTableModel;
    flight_model->setTable("flight");
    flight_model->select();

    flight_model->setHeaderData(0, Qt::Horizontal, "id летательного средства");
    flight_model->setHeaderData(1, Qt::Horizontal, "Дата и время вылета");
    flight_model->setHeaderData(2, Qt::Horizontal, "Рейс полёта");

    return flight_model;
}

bool Database::insertFlight(QString id_input, QString datetime_input, QString way_input)
{
    QSqlQuery query;
    query.prepare("INSERT INTO [" + name + "].[dbo].[flight] VALUES (" +
                  id_input + ", CAST('" +
                  datetime_input + "' AS DATETIME), '" +
                  way_input + "')");

    if (query.exec()){
        return true;
    } else {
        last_error = query.lastError();
        return false;
    }
}

bool Database::updateFlight(QString id_input, QString datetime_input, QString way_input, QString old_id, QString old_datetime, QString old_way)
{
    QSqlQuery query;
    query.prepare("UPDATE [" + name + "].[dbo].[flight] SET [vehicle_id]=" +
                  id_input + ", [flight_date]=CAST('" +
                  datetime_input + "' AS DATETIME), [way]='" +
                  way_input + "' WHERE vehicle_id=" + old_id + " AND flight_date=CAST('" + old_datetime + "' AS DATETIME) AND way LIKE '" + old_way + "'");

    if (query.exec()){
        return true;
    } else {
        last_error = query.lastError();
        return false;
    }
}

bool Database::deleteFlight(QString old_id, QString old_datetime, QString old_way)
{
    QSqlQuery query;
    query.prepare("DELETE FROM [" + name + "].[dbo].[flight] WHERE vehicle_id=" + old_id + " AND flight_date=CAST('" + old_datetime + "' AS DATETIME) AND way LIKE '" + old_way + "'");

    return query.exec();
}

QSqlTableModel *Database::getMaintenances()
{
    if (maintenance_model)
        delete maintenance_model;
    maintenance_model = new QSqlTableModel;
    maintenance_model->setTable("maintenance");
    maintenance_model->select();

    maintenance_model->setHeaderData(0, Qt::Horizontal, "id летательного средства");
    maintenance_model->setHeaderData(1, Qt::Horizontal, "Интервал обслуживания (дней)");
    maintenance_model->setHeaderData(2, Qt::Horizontal, "Тип обслуживания");
    maintenance_model->setHeaderData(3, Qt::Horizontal, "Объём (человеко-часов)");

    return maintenance_model;
}

bool Database::insertMaintenance(QString id_input, QString interval_input, QString type_input, QString volume_input)
{
    QSqlQuery query;
    query.prepare("INSERT INTO [" + name + "].[dbo].[maintenance] VALUES (" +
                  id_input + ", " +
                  interval_input + ", '" +
                  type_input + "', " +
                  volume_input + ")");

    if (query.exec()){
        return true;
    } else {
        last_error = query.lastError();
        return false;
    }
}

bool Database::updateMaintenance(QString id_input, QString interval_input, QString type_input, QString volume_input, QString old_id, QString old_interval, QString old_type, QString old_volume)
{
    QSqlQuery query;
    query.prepare("UPDATE [" + name + "].[dbo].[maintenance] SET [vehicle_id]=" +
                  id_input + ", [interval]=" +
                  interval_input + ", [type]='" +
                  type_input + "', [volume]=" +
                  volume_input + " WHERE vehicle_id=" + old_id + " AND interval=" + old_interval + " AND type LIKE '" + old_type + "' AND volume=" + old_volume);

    if (query.exec()){
        return true;
    } else {
        last_error = query.lastError();
        return false;
    }
}

bool Database::deleteMaintenance(QString old_id, QString old_interval, QString old_type, QString old_volume)
{
    QSqlQuery query;
    query.prepare("DELETE FROM [" + name + "].[dbo].[maintenance] WHERE vehicle_id=" + old_id + " AND interval=" + old_interval + " AND type LIKE '" + old_type + "' AND volume=" + old_volume);

    if (query.exec()){
        return true;
    } else {
        last_error = query.lastError();
        return false;
    }
}

QSqlError Database::getLastError()
{
    return last_error;
}
