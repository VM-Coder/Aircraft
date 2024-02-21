#ifndef EDITFLIGHT_H
#define EDITFLIGHT_H

#include <QWidget>

namespace Ui {
class EditFlight;
}

class EditFlight : public QWidget
{
    Q_OBJECT

public:
    QString id, datetime, way;

    explicit EditFlight(QWidget *parent = nullptr);
    ~EditFlight();    
    void setData(QString id_input, QString datetime_input, QString way_input);

private:
    Ui::EditFlight *ui;

signals:
    void edit_signal(QString id_input, QString datetime_input, QString way_input, QString old_id, QString old_datetime, QString old_way);
    void delete_signal(QString id_input, QString datetime_input, QString way_input);
private slots:
    void on_edit_button_clicked();
    void on_delete_button_clicked();
};

#endif // EDITFLIGHT_H
