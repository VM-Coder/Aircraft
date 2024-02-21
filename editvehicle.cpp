#include "editvehicle.h"
#include "ui_editvehicle.h"

EditVehicle::EditVehicle(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EditVehicle)
{
    ui->setupUi(this);
}

EditVehicle::~EditVehicle()
{
    delete ui;
}

void EditVehicle::setData(QString type_input, QString reg_input, QString model_input, QString owner_input, QString hours_input)
{
    this->ui->type_input->setText(type_input);
    this->ui->reg_input->setText(reg_input);
    this->ui->model_input->setText(model_input);
    this->ui->owner_input->setText(owner_input);
    this->ui->hours_input->setText(hours_input);
}

void EditVehicle::on_edit_button_clicked()
{
    emit edit_signal(
        ui->type_input->text(),
        ui->reg_input->text(),
        ui->model_input->text(),
        ui->owner_input->text(),
        ui->hours_input->text());

}


void EditVehicle::on_delete_button_clicked()
{
    emit delete_signal(this->vehicle_id);
}

