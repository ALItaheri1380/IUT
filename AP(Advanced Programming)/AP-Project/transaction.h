#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <QDialog>

namespace Ui {
class Transaction;
}

class Transaction : public QDialog
{
    Q_OBJECT

public:
    explicit Transaction(QWidget *parent = nullptr);
    void set(int p=0);
    ~Transaction();

    int getIndex_vector() const;
    void setIndex_vector(int newIndex_vector);

private slots:
    void on_pushButton_password_clicked();
    void on_pushButton_payment_clicked();

    void on_pushButton_cancel_clicked();

    void on_checkBox_robot_stateChanged(int arg1);

private:
    Ui::Transaction *ui;
    int pass{0};
    QString username{""};
    int index_vector;
};

#endif // TRANSACTION_H
