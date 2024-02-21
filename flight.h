#ifndef FLIGHT_H
#define FLIGHT_H

#include <QWidget>
#include <QtSql/QSqlTableModel>

#include "database.h"
#include "addflight.h"
#include "editflight.h"

namespace Ui {
class Flight;
}

class Flight : public QWidget
{
    Q_OBJECT

public:
    explicit Flight(Database* database, QWidget *parent = nullptr);
    ~Flight();

private slots:
    void on_tableView_clicked(const QModelIndex &index);

    void on_add_flight_clicked();

    void on_refresh_clicked();

private:
    Ui::Flight *ui;

    AddFlight* add_flight_window;
    EditFlight* edit_flight_window;
    Database* database;

public slots:
    void add_slot(QString id_input, QString datetime_input, QString way_input);
    void edit_slot(QString id_input, QString datetime_input, QString way_input, QString old_id, QString old_datetime, QString old_way);
    void delete_slot(QString id_input, QString datetime_input, QString way_input);

};

#endif // FLIGHT_H
