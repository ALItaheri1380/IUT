#include "client_registor.h"
#include "ui_client_registor.h"
#include <QFile>
client_registor::client_registor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::client_registor)
{
    ui->setupUi(this);
}

client_registor::~client_registor()
{
    delete ui;
}
void client_registor::final_regist(){
    read_file("Login_client.txt");
    Name.push_back(ui->lineEdit->text());
    Password.push_back(ui->lineEdit_2->text());
    Address_vect.push_back(ui->lineEdit_3->text());
    PhoneNumber.push_back(ui->lineEdit_4->text());
    Card_number.push_back(ui->lineEdit_5->text());
    cvv2.push_back(ui->lineEdit_6->text());
    Money.push_back(money_);
    write_to_file("Login_client.txt");
}
void client_registor::on_buttonBox_accepted()
{
    final_regist();
}
