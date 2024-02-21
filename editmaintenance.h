#ifndef EDITMAINTENANCE_H
#define EDITMAINTENANCE_H

#include <QWidget>

namespace Ui {
class EditMaintenance;
}

class EditMaintenance : public QWidget
{
    Q_OBJECT

public:
    QString id, interval, type, volume;

    explicit EditMaintenance(QWidget *parent = nullptr);
    ~EditMaintenance();
    void setData(QString id_input, QString interval_input, QString type_input, QString volume_input);

private:
    Ui::EditMaintenance *ui;

signals:
    void edit_signal(QString id_input, QString interval_input, QString type_input, QString volume_input, QString old_id, QString old_interval, QString old_type, QString old_volume);
    void delete_signal(QString id_input, QString interval_input, QString type_input, QString volume_input);
private slots:
    void on_edit_button_clicked();
    void on_delete_button_clicked();
};

#endif // EDITMAINTENANCE_H
