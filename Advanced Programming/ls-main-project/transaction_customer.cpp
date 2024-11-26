#include "transaction_customer.h"
#include "ui_transaction_customer.h"
#include "Global.h"
transaction_customer::transaction_customer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::transaction_customer)
{
    ui->setupUi(this);
    this->setFixedSize(601,196);
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
}

transaction_customer::~transaction_customer()
{
    delete ui;
}

void transaction_customer::on_pushButton_confirm_clicked()
{
    emit accept_item(1);
    this->close();

}
void transaction_customer::on_pushButton_cancel_clicked()
{
    this->close();
}

int transaction_customer::getIndex_vector() const
{
    return index_vector;
}

void transaction_customer::setIndex_vector(int newIndex_vector)
{
    index_vector = newIndex_vector;
}

