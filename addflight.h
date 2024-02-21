#ifndef ADDFLIGHT_H
#define ADDFLIGHT_H

#include <QWidget>

namespace Ui {
class AddFlight;
}

class AddFlight : public QWidget
{
    Q_OBJECT

public:
    explicit AddFlight(QWidget *parent = nullptr);
    ~AddFlight();

private slots:
    void on_add_button_clicked();

private:
    Ui::AddFlight *ui;

signals:
    void add_signal(QString id_input, QString datetime_input, QString way_input);

};

#endif // ADDFLIGHT_H
