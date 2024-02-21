#ifndef MAINTENANCE_H
#define MAINTENANCE_H

#include <QWidget>

#include "database.h"
#include "addmaintenance.h"
#include "editmaintenance.h"

namespace Ui {
class Maintenance;
}

class Maintenance : public QWidget
{
    Q_OBJECT

public:
    explicit Maintenance(Database* database, QWidget *parent = nullptr);
    ~Maintenance();

private slots:
    void on_tableView_clicked(const QModelIndex &index);

    void on_refresh_clicked();

    void on_add_flight_clicked();

private:
    Ui::Maintenance *ui;

    AddMaintenance* add_maintenance_window;
    EditMaintenance* edit_maintenance_window;
    Database* database;

public slots:
    void add_slot(QString id_input, QString interval_input, QString type_input, QString volume_input);
    void edit_slot(QString id_input, QString interval_input, QString type_input, QString volume_input, QString old_id, QString old_interval, QString old_type, QString old_volume);
    void delete_slot(QString old_id, QString old_interval, QString old_type, QString old_volume);
};



#endif // MAINTENANCE_H
