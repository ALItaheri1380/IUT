#include "increase_funds.h"
#include "ui_increase_funds.h"
#include <qpixmap.h>
#include <QMessageBox>
#include <QFile>
Increase_funds::Increase_funds(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Increase_funds)
{
    ui->setupUi(this);

}
Increase_funds::~Increase_funds()
{
    delete ui;
}
void Increase_funds::increas()
{

    read_file("Login_client.txt");
    bool is_valid = false;
    int i = 0;
    for(i ; i < Name.size() ; i++){
        if(Card_number[i] == ui->lineEdit->text()){
            is_valid = true;
            break;
        }

    }
    if(!is_valid)
    {
        int ret;
        QMessageBox msgBox;
        msgBox.setText("این شماره کارت وجود ندارد!!!!");
        ret = msgBox.exec();
        return;
    }
    if(ui->lineEdit_2->text() == cvv2[i]&&
             ui->lineEdit_3->text() == Password[i])
        {
             int M = Money[i].toInt();
             M = M + ui->lineEdit_4->text().toInt();
             Money.replace(i,QVariant(M).toString());
             write_to_file("Login_client.txt");
             int ret;
             QMessageBox msgBox;
             msgBox.setText("افزایش وجه با موفقیت انجام شد :)))))");
             ret = msgBox.exec();
             return;
        }
    else{
        int ret;
        QMessageBox msgBox;
        msgBox.setText("رمز یا سی وی وی 2 اشتباه است !!!! ");
        ret = msgBox.exec();
        return;
    }
}
void Increase_funds::on_buttonBox_accepted()
{
     increas();
}
