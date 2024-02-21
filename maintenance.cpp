#include "maintenance.h"
#include "ui_maintenance.h"
#include "QMessageBox"

Maintenance::Maintenance(Database* database, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Maintenance)
{
    this->database = database;
    ui->setupUi(this);

    ui->tableView->setModel(database->getMaintenances());
}

Maintenance::~Maintenance()
{
    delete ui;
}

void Maintenance::on_tableView_clicked(const QModelIndex &index)
{
    QString fields[4];
    for (int i = 0; i < 4; i++){
        fields[i] = index.sibling(index.row(), i).data().toString();
    }

    edit_maintenance_window = new EditMaintenance();
    edit_maintenance_window->setData(fields[0], fields[1], fields[2], fields[3]);
    edit_maintenance_window->show();

    edit_maintenance_window->setWindowTitle("Edit Maintenance");

    connect(edit_maintenance_window, &EditMaintenance::edit_signal, this, &Maintenance::edit_slot);
    connect(edit_maintenance_window, &EditMaintenance::delete_signal, this, &Maintenance::delete_slot);
}


void Maintenance::on_refresh_clicked()
{
    ui->tableView->setModel(database->getMaintenances());
}


void Maintenance::on_add_flight_clicked()
{
    add_maintenance_window = new AddMaintenance();
    add_maintenance_window->show();

    add_maintenance_window->setWindowTitle("Add Maintenance");

    connect(add_maintenance_window, &AddMaintenance::add_signal, this, &Maintenance::add_slot);
}

void Maintenance::add_slot(QString id_input, QString interval_input, QString type_input, QString volume_input)
{
    if (database->insertMaintenance(id_input, interval_input, type_input, volume_input)){
        add_maintenance_window->close();
    } else {
        QMessageBox qmessage;
        qmessage.setText("Ошибка выполнения запроса\n" + database->getLastError().text());
        qmessage.setIcon(QMessageBox::Critical);
        qmessage.setDefaultButton(QMessageBox::Ok);
        qmessage.exec();
    }
}

void Maintenance::edit_slot(QString id_input, QString interval_input, QString type_input, QString volume_input, QString old_id, QString old_interval, QString old_type, QString old_volume)
{
    if (database->updateMaintenance(id_input, interval_input, type_input, volume_input, old_id, old_interval, old_type, old_volume)){
        edit_maintenance_window->close();
    } else {
        QMessageBox qmessage;
        qmessage.setText("Ошибка выполнения запроса\n" + database->getLastError().text());
        qmessage.setIcon(QMessageBox::Critical);
        qmessage.setDefaultButton(QMessageBox::Ok);
        qmessage.exec();
    }
}

void Maintenance::delete_slot(QString old_id, QString old_interval, QString old_type, QString old_volume)
{
    QMessageBox qmessage;
    qmessage.setText("Вы уверены, что хотите удалить информацию об этом техобслуживании?");
    qmessage.setIcon(QMessageBox::Question);
    qmessage.addButton(QMessageBox::No);
    qmessage.addButton(QMessageBox::Yes);

    if (qmessage.exec() == QMessageBox::No){
        return;
    }

    if (database->deleteMaintenance(old_id, old_interval, old_type, old_volume)){
        edit_maintenance_window->close();
    } else {
        QMessageBox qmessage;
        qmessage.setText("Ошибка выполнения запроса\n" + database->getLastError().text());
        qmessage.setIcon(QMessageBox::Critical);
        qmessage.setDefaultButton(QMessageBox::Ok);
        qmessage.exec();
    }
}

