#include "addmaintenance.h"
#include "ui_addmaintenance.h"

AddMaintenance::AddMaintenance(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddMaintenance)
{
    ui->setupUi(this);
}

AddMaintenance::~AddMaintenance()
{
    delete ui;
}

void AddMaintenance::on_add_button_clicked()
{
    emit add_signal(
        ui->id_input->text(),
        ui->interval_input->text(),
        ui->type_input->text(),
        ui->volume_input->text());
}

