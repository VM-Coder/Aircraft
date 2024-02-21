#include "flight.h"
#include "ui_flight.h"
#include "QMessageBox"
#include "QDateTime"

Flight::Flight(Database* database, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Flight)
{
    this->database = database;
    ui->setupUi(this);

    ui->tableView->setModel(database->getFlights());
}

Flight::~Flight()
{
    delete ui;
}

void Flight::toDocx()
{

}

void Flight::add_slot(QString id_input, QString datetime_input, QString way_input)
{
    if (database->insertFlight(id_input, datetime_input, way_input)){
        add_flight_window->close();
    } else {
        QMessageBox qmessage;
        qmessage.setText("Ошибка выполнения запроса\n" + database->getLastError().text());
        qmessage.setIcon(QMessageBox::Critical);
        qmessage.setDefaultButton(QMessageBox::Ok);
        qmessage.exec();
    }
}

void Flight::edit_slot(QString id_input, QString datetime_input, QString way_input, QString old_id, QString old_datetime, QString old_way)
{
    if (database->updateFlight(id_input, datetime_input, way_input, old_id, old_datetime, old_way)){
        edit_flight_window->close();
    } else {
        QMessageBox qmessage;
        qmessage.setText("Ошибка выполнения запроса\n" + database->getLastError().text());
        qmessage.setIcon(QMessageBox::Critical);
        qmessage.setDefaultButton(QMessageBox::Ok);
        qmessage.exec();
    }
}

void Flight::delete_slot(QString id_input, QString datetime_input, QString way_input)
{
    QMessageBox qmessage;
    qmessage.setText("Вы уверены, что хотите удалить информацию об этом вылете?");
    qmessage.setIcon(QMessageBox::Question);
    qmessage.addButton(QMessageBox::No);
    qmessage.addButton(QMessageBox::Yes);

    if (qmessage.exec() == QMessageBox::No){
        return;
    }

    if (database->deleteFlight(id_input, datetime_input, way_input)){
        edit_flight_window->close();
    } else {
        QMessageBox qmessage;
        qmessage.setText("Ошибка выполнения запроса\n" + database->getLastError().text());
        qmessage.setIcon(QMessageBox::Critical);
        qmessage.setDefaultButton(QMessageBox::Ok);
        qmessage.exec();
    }
}

void Flight::on_tableView_clicked(const QModelIndex &index)
{
    QString fields[3];
    for (int i = 0; i < 3; i++){
        fields[i] = index.sibling(index.row(), i).data().toString();
    }

    QDateTime qdt = QDateTime::fromString(fields[1].replace("T", " "), "yyyy-MM-dd hh:mm:ss.zzz");
    fields[1] = qdt.toString("dd.MM.yyyy hh:mm");

    edit_flight_window = new EditFlight();
    edit_flight_window->setData(fields[0], fields[1], fields[2]);
    edit_flight_window->show();

    edit_flight_window->setWindowTitle("Edit Flight");

    connect(edit_flight_window, &EditFlight::edit_signal, this, &Flight::edit_slot);
    connect(edit_flight_window, &EditFlight::delete_signal, this, &Flight::delete_slot);
}


void Flight::on_add_flight_clicked()
{
    add_flight_window = new AddFlight();
    add_flight_window->show();

    add_flight_window->setWindowTitle("Add Flight");

    connect(add_flight_window, &AddFlight::add_signal, this, &Flight::add_slot);
}


void Flight::on_refresh_clicked()
{
    ui->tableView->setModel(database->getFlights());
}



