#include "chenge_information.h"
#include "ui_chenge_information.h"
#include"chenge_info_client.h"
#include"chenge_info_cus.h"
chenge_information::chenge_information(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::chenge_information)
{
    ui->setupUi(this);
}

chenge_information::~chenge_information()
{
    delete ui;
}

void chenge_information::on_pushButton_clicked()
{
    chenge_info_client* d = new chenge_info_client(this);
    d->show();
}


void chenge_information::on_pushButton_2_clicked()
{
    chenge_info_cus* d = new chenge_info_cus(this);
    d->show();
}

