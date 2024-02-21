#include "editflight.h"
#include "ui_editflight.h"

EditFlight::EditFlight(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EditFlight)
{
    ui->setupUi(this);
    ui->datetime_input->setInputMask("99.99.9999 99:99");
}

EditFlight::~EditFlight()
{
    delete ui;
}

void EditFlight::setData(QString id_input, QString datetime_input, QString way_input)
{
    this->ui->id_input->setText(id_input);
    this->ui->datetime_input->setText(datetime_input);
    this->ui->way_input->setText(way_input);

    this->id = id_input;
    this->datetime = datetime_input;
    this->way = way_input;
}

void EditFlight::on_edit_button_clicked()
{
    emit edit_signal(
        ui->id_input->text(),
        ui->datetime_input->text(),
        ui->way_input->text(),
        this->id,
        this->datetime,
        this->way);
}


void EditFlight::on_delete_button_clicked()
{
    emit delete_signal(
        this->id,
        this->datetime,
        this->way);
}

