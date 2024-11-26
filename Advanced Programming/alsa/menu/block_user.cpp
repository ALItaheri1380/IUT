#include "block_user.h"
#include "ui_block_user.h"
#include<QFile>
block_user::block_user(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::block_user)
{
    ui->setupUi(this);
}

block_user::~block_user()
{
    delete ui;
}
void block_user::on_buttonBox_accepted()
{
    QString user_name = ui->lineEdit->text();
    Read_file();
    bool check = false;
    for (int i = 0 ; i <name.size() ; i++){
        if(name[i] == user_name){
            check = true;
            Block.replace(i,"block");
            break;
        }
    }
    if(check)
        Write_to_file();
}
