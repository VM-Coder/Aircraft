#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "QMessageBox"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //this->setAttribute(Qt::WA_QuitOnClose);

    login_window = new Login();
    login_window->show();
    login_window->setWindowTitle("Login");

    database = new Database();

    connect(login_window, &Login::connect_signal, this, &MainWindow::connect_slot);
    //qDebug() << QSqlDatabase::drivers();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::connect_slot(QString server_input, QString database_input, QString login_input, QString password_input)
{
    database->Init(
        server_input,
        database_input,
        login_input,
        password_input);

    if (database->open()){
        this->show();
        login_window->close();

        ui->tableView->setModel(database->getVehicles());
        ui->tableView->verticalHeader()->hide();
        ui->tableView->horizontalHeader()->sectionResizeMode(QHeaderView::ResizeToContents);


    } else {

        QMessageBox qmessage;
        qmessage.setText("Ошибка подключения к базе\n" + database->getLastError().text());
        qmessage.setIcon(QMessageBox::Critical);
        qmessage.setDefaultButton(QMessageBox::Ok);
        qmessage.exec();
    }


}

void MainWindow::add_slot(QString type_input, QString reg_input, QString model_input, QString owner_input, QString hours_input)
{
    if (database->insertVehicle(type_input, reg_input, model_input, owner_input, hours_input)){
        add_vehicle_window->close();
    } else {
        QMessageBox qmessage;
        qmessage.setText("Ошибка выполнения запроса\n" + database->getLastError().text());
        qmessage.setIcon(QMessageBox::Critical);
        qmessage.setDefaultButton(QMessageBox::Ok);
        qmessage.exec();
    }
}

void MainWindow::edit_slot(QString type_input, QString reg_input, QString model_input, QString owner_input, QString hours_input)
{
    if (database->updateVehicle(type_input, reg_input, model_input, owner_input, hours_input, edit_vehicle_window->vehicle_id)){
        edit_vehicle_window->close();
    } else {
        QMessageBox qmessage;
        qmessage.setText("Ошибка выполнения запроса\n" + database->getLastError().text());
        qmessage.setIcon(QMessageBox::Critical);
        qmessage.setDefaultButton(QMessageBox::Ok);
        qmessage.exec();
    }
}

void MainWindow::delete_slot(QString id)
{
    QMessageBox qmessage;
    qmessage.setText("Удаление летательного средства из базы приведёт к удалению всех связанных с ним записей. Вы уверены, что хотите удалить летательное средство?");
    qmessage.setIcon(QMessageBox::Question);
    qmessage.addButton(QMessageBox::No);
    qmessage.addButton(QMessageBox::Yes);

    if (qmessage.exec() == QMessageBox::No){
        return;
    }

    if (database->deleteVehicle(edit_vehicle_window->vehicle_id)){
        edit_vehicle_window->close();
    } else {
        QMessageBox qmessage;
        qmessage.setText("Ошибка выполнения запроса\n" + database->getLastError().text());
        qmessage.setIcon(QMessageBox::Critical);
        qmessage.setDefaultButton(QMessageBox::Ok);
        qmessage.exec();
    }
}


void MainWindow::on_refresh_triggered()
{
    ui->tableView->setModel(database->getVehicles());
}


void MainWindow::on_add_vehicle_triggered()
{
    add_vehicle_window = new AddVehicle();
    add_vehicle_window->show();

    add_vehicle_window->setWindowTitle("Add Vehicle");

    connect(add_vehicle_window, &AddVehicle::add_signal, this, &MainWindow::add_slot);
}

void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    QString fields[6];
    for (int i = 0; i < 6; i++){
        fields[i] = index.sibling(index.row(), i).data().toString();
    }

    edit_vehicle_window = new EditVehicle();
    edit_vehicle_window->vehicle_id = fields[0];
    edit_vehicle_window->setData(fields[1], fields[2], fields[3], fields[4], fields[5]);
    edit_vehicle_window->show();

    edit_vehicle_window->setWindowTitle("Edit Vehicle");

    connect(edit_vehicle_window, &EditVehicle::edit_signal, this, &MainWindow::edit_slot);
    connect(edit_vehicle_window, &EditVehicle::delete_signal, this, &MainWindow::delete_slot);
}


void MainWindow::on_MainWindow_destroyed()
{
    exit(0);
}

void MainWindow::on_flight_triggered()
{
    flight_window = new Flight(database);
    flight_window->show();

    flight_window->setWindowTitle("Flights");
}


void MainWindow::on_maintenance_triggered()
{
    maintenance_window = new Maintenance(database);
    maintenance_window->show();

    maintenance_window->setWindowTitle("Maintenance");
}


void MainWindow::on_show_help_triggered()
{
    help_window = new Help();
    help_window->show();

    help_window->setWindowTitle("Help");
}

