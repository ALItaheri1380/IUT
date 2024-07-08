#include "list_accounts.h"
#include "ui_list_accounts.h"
#include "show_accounts.h"

list_accounts::list_accounts(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::list_accounts)
{
    ui->setupUi(this);
}

list_accounts::~list_accounts()
{
    delete ui;
}

void list_accounts::on_pushButton_3_clicked()
{
    close();
}


void list_accounts::on_pushButton_clicked()
{
    show_accounts* temp = new show_accounts{this};
    connect(this, SIGNAL(sendUserName(QString)), temp, SLOT(getUserName(QString)));

    temp->show();
    emit sendUserName("customer");
}


void list_accounts::on_pushButton_2_clicked()
{
    show_accounts* temp = new show_accounts{this};
    connect(this, SIGNAL(sendUserName(QString)), temp, SLOT(getUserName(QString)));

    temp->show();
    emit sendUserName("client");
}

