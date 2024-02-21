#include "addvehicle.h"
#include "ui_addvehicle.h"

AddVehicle::AddVehicle(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddVehicle)
{
    ui->setupUi(this);
}

AddVehicle::~AddVehicle()
{
    delete ui;
}

void AddVehicle::on_add_button_clicked()
{
    emit add_signal(
            ui->type_input->text(),
            ui->reg_input->text(),
            ui->model_input->text(),
            ui->owner_input->text(),
            ui->hours_input->text());
}

