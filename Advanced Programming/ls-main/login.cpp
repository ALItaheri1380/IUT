#include "login.h"
#include "ui_login.h"
#include "create_account.h"
#include "forget_password.h"
#include<QString>
#include <iostream>
#include "time.h"
#include "QDebug"
#include "QMessageBox"
#include "admin.h"
#include "client.h"
#include "customer.h"
#include "game.h"
#include "mythered.h"
bool exit1=0;
void login::check_correct_password(QString user_name, QString password)
{
    Global glob;
    exit1=0;
    for(int i=0;i<glob.vec_person.size();i++)
    {
        QString u=glob.vec_person[i].get_user_name() , p=glob.vec_person[i].get_password();
        if(user_name==u && password==p)
        {
            exit1=1;
            if(glob.vec_person[i].get_ban())
            {
                QMessageBox *qm = new QMessageBox(this);
                qm->setText("Account Baned");
                qm->exec();

            }
            else
            {
                if (glob.vec_person[i].get_type()==0)
                {
                    mythered *x=new mythered;
                    x->set(0,glob.vec_person[i]);
                    x->run();
                }
                else if(glob.vec_person[i].get_type()==1)
                {
                    mythered *x=new mythered;
                    x->set(1,glob.vec_person[i]);
                    x->run();
                }
                else
                {
                    mythered *x=new mythered;
                    x->set(2,glob.vec_person[i]);
                    x->run();
                }
            }
        }
    }
    if(exit1==0)
    {
        QMessageBox *qm = new QMessageBox(this);
        qm->setText("invalid password or username");
        qm->exec();
    }
}
login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    this->setFixedSize(954,581);
    ui->setupUi(this);
    setWindowTitle("AP_Store2022");
    Global::load();
    Global::load_article();
    Global::load_buyer();
    Global::load_tran();
    srand(time(0));
    int a=rand()%(51);
    int b=rand()%(51);
    sum=a+b;
    QString x=QString::number(a);
    QString y=QString::number(b);

    ui->label_4->setText("Enter the Answer "+x+"+"+y+" =");
    ui->lineEdit_sum->hide();
    ui->lineEdit_sum->show();

}


login::~login()
{
    delete ui;
}



void login::on_pushButton_Creat_clicked()
{
   Create_account *d=new Create_account(this);
   d->show();
}


void login::on_commandLinkButton_clicked()
{
    forget_password *d=new forget_password(this);
    d->show();
}


void login::on_pushButton_Login_clicked()
{

    QString password , user_name;
    user_name=ui->lineEdit_name->text();
    password = ui->lineEdit_password->text();
    int x=ui->lineEdit_sum->text().toInt();
    if (sum == x)
    {
            ui->lineEdit_sum->setStyleSheet("background: rgb(255,255,255);");
    }
    if (!(ui->lineEdit_name->text().isEmpty()&& ui->lineEdit_password->text().isEmpty()))
    {
        ui->lineEdit_name->setStyleSheet("background: rgb(255,255,255);");
        ui->lineEdit_password->setStyleSheet("background: rgb(255,255,255);");
    }
    if ((ui->lineEdit_name->text().isEmpty()&& ui->lineEdit_password->text().isEmpty()))
    {
        ui->lineEdit_name->setStyleSheet("background: rgb(255,0,0);");
        ui->lineEdit_password->setStyleSheet("background: rgb(255,0,0);");
    }
    else if (ui->lineEdit_password->text().isEmpty())
    {
        ui->lineEdit_name->setStyleSheet("background: rgb(255,255,255);");
        ui->lineEdit_password->setStyleSheet("background: rgb(255,0,0);");
    }
    else if(ui->lineEdit_name->text().isEmpty())
    {
        ui->lineEdit_password->setStyleSheet("background: rgb(255,255,255);");
        ui->lineEdit_name->setStyleSheet("background: rgb(255,0,0);");
    }

    else if (sum == x)
    {
        ui->lineEdit_sum->setStyleSheet("background: rgb(255,255,255);");
        check_correct_password(user_name, password);
    }
    if(sum!=x)
    {
        ui->lineEdit_sum->setStyleSheet("background: rgb(255,0,0);");
    }
    int a=rand()%(51);
    int b=rand()%(51);
    sum=a+b;
    QString xx=QString::number(a);
    QString y=QString::number(b);
    ui->label_4->setText("");
    ui->label_4->setText(ui->label_4->text()+"Enter the Answer "+xx+"+"+y+" =");
}


