#include "forget_pasword_customer.h"
#include "ui_forget_pasword_customer.h"
#include <QMessageBox>
#include <QFile>
forget_pasword_customer::forget_pasword_customer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::forget_pasword_customer)
{
    ui->setupUi(this);
}
forget_pasword_customer::~forget_pasword_customer()
{
    delete ui;
}
void forget_pasword_customer::on_buttonBox_accepted()
{
    Read_file();
    int i = 0;
    for(i  ; i < name.size() ; i++ ){
        if(ui->lineEdit->text() == name[i]){
            isvalid = true;
            break;
        }
    }
    chekVal(isvalid);
    if(isvalid){
          password.replace(i,ui->lineEdit_2->text());
          Write_to_file();
       }
}
