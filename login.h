#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>

namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

public slots:
    void on_connect_button_clicked();

private:
    Ui::Login *ui;

signals:
    void connect_signal(QString server_input, QString database_input, QString login_input, QString password_input);
};



#endif // LOGIN_H
