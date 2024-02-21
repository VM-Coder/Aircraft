#ifndef ADDVEHICLE_H
#define ADDVEHICLE_H

#include <QWidget>

namespace Ui {
class AddVehicle;
}

class AddVehicle : public QWidget
{
    Q_OBJECT

public:
    explicit AddVehicle(QWidget *parent = nullptr);
    ~AddVehicle();

private slots:
    void on_add_button_clicked();

private:
    Ui::AddVehicle *ui;

signals:
    void add_signal(QString type_input, QString reg_input, QString model_input, QString owner_input, QString hours_input);
};

#endif // ADDVEHICLE_H
