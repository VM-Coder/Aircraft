#include "addflight.h"
#include "ui_addflight.h"

AddFlight::AddFlight(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddFlight)
{
    ui->setupUi(this);
    ui->datetime_input->setInputMask("99.99.9999 99:99");
}

AddFlight::~AddFlight()
{
    delete ui;
}


void AddFlight::on_add_button_clicked()
{
    emit add_signal(
        ui->id_input->text(),
        ui->datetime_input->text(),
        ui->way_input->text());
}

