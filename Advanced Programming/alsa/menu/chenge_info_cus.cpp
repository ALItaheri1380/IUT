#include "chenge_info_cus.h"
#include "ui_chenge_info_cus.h"
#include <QMessageBox>
chenge_info_cus::chenge_info_cus(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::chenge_info_cus)
{
    ui->setupUi(this);
}

chenge_info_cus::~chenge_info_cus()
{
    delete ui;
}

void chenge_info_cus::on_buttonBox_accepted()
{
    Read_file();
    int i = 0;
   bool isvalid = false;
    for (i ; i < name.size() ; i++){
        if(name[i] == ui->lineEdit->text()){
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
    CVV2.replace(i,ui->lineEdit_3->text());
    card_number.replace(i,ui->lineEdit_2->text());
    Write_to_file();
    int ret;
    QMessageBox msgBox;
    msgBox.setText("عملیات با موفقیت انجام شد:)))))");
    ret = msgBox.exec();
}

