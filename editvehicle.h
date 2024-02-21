#ifndef EDITVEHICLE_H
#define EDITVEHICLE_H

#include <QWidget>

namespace Ui {
class EditVehicle;
}

class EditVehicle : public QWidget
{
    Q_OBJECT

public:
    QString vehicle_id;

    explicit EditVehicle(QWidget *parent = nullptr);
    ~EditVehicle();
    void setData(QString type_input, QString reg_input, QString model_input, QString owner_input, QString hours_input);

private:
    Ui::EditVehicle *ui;


signals:
    void edit_signal(QString type_input, QString reg_input, QString model_input, QString owner_input, QString hours_input);
    void delete_signal(QString id);
private slots:
    void on_edit_button_clicked();
    void on_delete_button_clicked();
};

#endif // EDITVEHICLE_H
