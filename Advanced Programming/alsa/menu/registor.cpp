#include "registor.h"
#include "ui_registor.h"
#include <QMessageBox>
#include <QFile>
Registor::Registor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Registor)
{
    ui->setupUi(this);
}
Registor::~Registor()
{
    delete ui;
}
void Registor::final_regist()
{
    QString unBlock = "unblock";
    card_number.push_back(ui->lineEdit->text());
    CVV2.push_back(ui->lineEdit_2->text());
    password.push_back(ui->lineEdit_3->text());
    name.push_back(ui->lineEdit_4->text());
    money.push_back(money_);
    Block.push_back(unBlock);
    Write_to_file();
}
void Registor::on_buttonBox_accepted()
{
    Read_file();
    bool isvalid = false;
    bool isvalid2 = false;
    for(int i =0 ; i < name.size() ; i++){
        if(password[i]==ui->lineEdit_3->text()){
            isvalid  = true;
            break;
        }
    }
    for(int i = 0 ; i < name.size() ; i++){
        if(name[i]==ui->lineEdit_4->text()){
            isvalid2 = true;
            break;
        }
    }
    if(!isvalid&&!isvalid2){
        final_regist();
        return;
    }
     if(isvalid2){
         QMessageBox msgBox;
        msgBox.setText("نام کاربری تکراری است!!!!!");
        int ret = msgBox.exec();
        return;
     }
    if(isvalid){
        QMessageBox msgBox;
       msgBox.setText("رمز تکراری است!!!!!");
       int ret = msgBox.exec();
       return;
    }
}
