#include "chenge_info_client.h"
#include "ui_chenge_info_client.h"
#include <QMessageBox>
chenge_info_client::chenge_info_client(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::chenge_info_client)
{
    ui->setupUi(this);
}

chenge_info_client::~chenge_info_client()
{
    delete ui;
}

void chenge_info_client::on_buttonBox_accepted()
{
    read_file("Login_client.txt");
    int i = 0;
   bool isvalid = false;
    for (i ; i < Name.size() ; i++){
        if(Name[i] == ui->lineEdit->text()){
            isvalid = true;
            break;
        }
    }
    if(!isvalid){
        int ret;
        QMessageBox msgBox;
        msgBox.setText("این کاربر وجود ندارد !!!!!");
        ret = msgBox.exec();
        return;
    }
    PhoneNumber.replace(i,ui->lineEdit_3->text());
    Address_vect.replace(i,ui->lineEdit_2->text());
    write_to_file("Login_client.txt");
    int ret;
    QMessageBox msgBox;
    msgBox.setText("عملیات با موفقیت انجام شد:)))))");
    ret = msgBox.exec();
}

