#ifndef INCREASE_FUNDS_H
#define INCREASE_FUNDS_H
#include"persongclientt.h"
#include"global_payment.h"
#include <QDialog>

namespace Ui {
class Increase_funds;
}

class Increase_funds : public QDialog,public personGclientt,global_Payment
{
    Q_OBJECT

public:
    explicit Increase_funds(QWidget *parent = nullptr);
    ~Increase_funds();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::Increase_funds *ui;
    void increas();
};

#endif // INCREASE_FUNDS_H
