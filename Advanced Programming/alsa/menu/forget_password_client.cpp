#include "forget_password_client.h"
#include "ui_forget_password_client.h"
#include <QFile>
#include <QMessageBox>
forget_password_client::forget_password_client(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::forget_password_client)
{
    ui->setupUi(this);
}
forget_password_client::~forget_password_client()
{
    delete ui;
}

void forget_password_client::on_buttonBox_accepted()
{
       read_file("Login_client.txt");
        int i=0;
         for(i ; i < Name.size() ; i++){
            if(Name[i] == ui->lineEdit->text()){
                isvalid = true;
                break;
            }
        }
         chekVal(isvalid);
        if(isvalid){
           Password.replace(i,ui->lineEdit_2->text());
           write_to_file("Login_client.txt");
        }
}
