#include "delete_user.h"
#include "ui_delete_user.h"
#include"delete_client.h"
#include"delete_cus.h"
delete_user::delete_user(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::delete_user)
{
    ui->setupUi(this);
}

delete_user::~delete_user()
{
    delete ui;
}

void delete_user::on_pushButton_clicked()
{
    delete_client* d = new delete_client(this);
    d->show();
}


void delete_user::on_pushButton_2_clicked()
{
    delete_cus* d = new delete_cus(this);
    d->show();
}

