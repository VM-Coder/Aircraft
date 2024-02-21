#include "editmaintenance.h"
#include "ui_editmaintenance.h"

EditMaintenance::EditMaintenance(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EditMaintenance)
{
    ui->setupUi(this);
}

EditMaintenance::~EditMaintenance()
{
    delete ui;
}

void EditMaintenance::setData(QString id_input, QString interval_input, QString type_input, QString volume_input)
{
    this->ui->id_input->setText(id_input);
    this->ui->interval_input->setText(interval_input);
    this->ui->type_input->setText(type_input);
    this->ui->volume_input->setText(volume_input);

    this->id = id_input;
    this->interval = interval_input;
    this->type = type_input;
    this->volume = volume_input;
}

void EditMaintenance::on_edit_button_clicked()
{
    emit edit_signal(
        ui->id_input->text(),
        ui->interval_input->text(),
        ui->type_input->text(),
        ui->volume_input->text(),
        this->id,
        this->interval,
        this->type,
        this->volume);
}


void EditMaintenance::on_delete_button_clicked()
{
    emit delete_signal(
        this->id,
        this->interval,
        this->type,
        this->volume);
}

