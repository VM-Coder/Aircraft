#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);

    ui->password_input->setEchoMode(QLineEdit::Password);
}

Login::~Login()
{
    delete ui;
}

void Login::on_connect_button_clicked()
{
    emit connect_signal(
            ui->server_input->text(),
            ui->database_input->text(),
            ui->login_input->text(),
            ui->password_input->text());

}

