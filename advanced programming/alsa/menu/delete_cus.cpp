#include "delete_cus.h"
#include "ui_delete_cus.h"
#include <QMessageBox>
delete_cus::delete_cus(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::delete_cus)
{
    ui->setupUi(this);
}

delete_cus::~delete_cus()
{
    delete ui;
}

void delete_cus::on_buttonBox_accepted()
{
    Read_file();
    int i = 0 ;
    bool check = false;
    for (i ;  i < name.size() ; i++ ){
        if(name[i] == ui->lineEdit->text()){
            check = true;
            break;
        }
    }
    if(!check){
        int ret;
        QMessageBox msgBox;
        msgBox.setText("این کاربر وجود ندارد !!!!!");
        ret = msgBox.exec();
        return;
    }
    name.remove(i);
    password.remove(i);
    card_number.remove(i);
    CVV2.remove(i);
    money.remove(i);
    Write_to_file();
    int ret;
    QMessageBox msgBox;
    msgBox.setText(" فروشنده  با موفقیت حذف شد:)))))");
    ret = msgBox.exec();
    return;
}

