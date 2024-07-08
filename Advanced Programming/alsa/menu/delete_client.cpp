#include "delete_client.h"
#include "ui_delete_client.h"
#include <QMessageBox>
delete_client::delete_client(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::delete_client)
{
    ui->setupUi(this);
}

delete_client::~delete_client()
{
    delete ui;
}

void delete_client::on_buttonBox_accepted()
{
    read_file("Login_client.txt");
    int i = 0 ;
    bool check = false;
    for (i ;  i < Name.size() ; i++ ){
        if(Name[i] == ui->lineEdit->text()){
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
    Name.remove(i);
    Address_vect.remove(i);
    PhoneNumber.remove(i);
    Password.remove(i);
    Card_number.remove(i);
    cvv2.remove(i);
    Money.remove(i);
    write_to_file("Login_client.txt");
    int ret;
    QMessageBox msgBox;
    msgBox.setText("خریدار  با موفقیت حذف شد:)))))");
    ret = msgBox.exec();
    return;
}

