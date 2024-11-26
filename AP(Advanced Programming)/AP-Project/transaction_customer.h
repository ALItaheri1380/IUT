#ifndef TRANSACTION_CUSTOMER_H
#define TRANSACTION_CUSTOMER_H

#include <QDialog>

namespace Ui {
class transaction_customer;
}

class transaction_customer : public QDialog
{
    Q_OBJECT

public:
    explicit transaction_customer(QWidget *parent = nullptr);
    ~transaction_customer();

    int getIndex_vector() const;
    void setIndex_vector(int newIndex_vector);

private slots:
    void on_pushButton_confirm_clicked();

    void on_pushButton_cancel_clicked();
signals:
    void accept_item(int);

private:
    Ui::transaction_customer *ui;
    int index_vector;
};

#endif // TRANSACTION_CUSTOMER_H
