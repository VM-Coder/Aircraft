#ifndef ADDMAINTENANCE_H
#define ADDMAINTENANCE_H

#include <QWidget>

namespace Ui {
class AddMaintenance;
}

class AddMaintenance : public QWidget
{
    Q_OBJECT

public:
    explicit AddMaintenance(QWidget *parent = nullptr);
    ~AddMaintenance();

private slots:
    void on_add_button_clicked();

private:
    Ui::AddMaintenance *ui;

signals:
    void add_signal(QString id_input, QString interval_input, QString type_input, QString volume_input);

};

#endif // ADDMAINTENANCE_H
