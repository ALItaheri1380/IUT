#include "unblock.h"
#include "ui_unblock.h"

unblock::unblock(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::unblock)
{
    ui->setupUi(this);
}

unblock::~unblock()
{
    delete ui;
}

void unblock::on_buttonBox_accepted()
{
    QString user_name = ui->lineEdit->text();
    Read_file();
    bool check = false;
    for (int i = 0 ; i <name.size() ; i++){
        if(name[i] == user_name){
            check = true;
            Block.replace(i,"unblock");
            break;
        }
    }
    if(check)
        Write_to_file();
}

