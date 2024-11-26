#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "registor.h"
#include "client_registor.h"
#include "forget_pasword_customer.h"
#include "forget_password_client.h"
#include "admin.h"
#include <QFile>
#include <QMessageBox>
#include "custumer_menu.h"
#include "client_meno.h"
#include<QProcess>

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent)
        , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
    Registor *d = new Registor(this);
    d->show();
}

void MainWindow::on_pushButton_5_clicked()
{
    client_registor *d = new client_registor(this);
    d->show();
}

void MainWindow::on_pushButton_clicked()
{
    forget_pasword_customer *d = new forget_pasword_customer(this);
    d->show();
}

void MainWindow::on_pushButton_6_clicked()
{
    forget_password_client *d = new forget_password_client(this);
    d->show();
}

void MainWindow::on_pushButton_3_clicked()
{
    exit(0);
}

void MainWindow::on_pushButton_4_clicked()
{
    if(ui->lineEdit->text() == "admin" && ui->lineEdit_2->text() =="admin" ){
        Admin *d = new Admin;
        close();
        d->show();
    }
    else if(ui->lineEdit->text() == "customer"){
        Read_file();
        bool isvalid = false;
        int i = 0;
        for(i ; i < password.size() ; i++){
            if(password[i] == ui->lineEdit_2->text()){
                isvalid = true;
                break;
            }
        }
        if(!isvalid){
            int ret;
            QMessageBox msgBox;
            msgBox.setText("رمز اشتباه است!!!!");
            ui->lineEdit->clear();
            ui->lineEdit_2->clear();
            ret = msgBox.exec();
            return;
        }
        
        if(Block[i]!="unblock"){
            int ret;
            QMessageBox msgBox;
            msgBox.setText("دسترسی شما به سایت به علت بلاک بودن محدود شده است!!!");
            ui->lineEdit->clear();
            ui->lineEdit_2->clear();
            ret = msgBox.exec();
            return;
        }
        else
        {
            custumer_menu* temp = new custumer_menu();
            temp->show();
            connect(this, SIGNAL(sendUserName(QString)), temp, SLOT(getUserName(QString)));
            emit sendUserName(ui->lineEdit_2->text());
            close();
        }
    }
    else{
        read_file("Login_client.txt");
        bool isvalid = false;
        for(int i = 0 ; i < Name.size() ; i++){
            if(ui->lineEdit->text() == Name [i] && ui->lineEdit_2->text() == Password[i]){
                isvalid = true;
                break;
            }
        }
        if(!isvalid){
            int ret;
            QMessageBox msgBox;
            msgBox.setText("رمز یا نام کاربری اشتباه است!!!");
            ui->lineEdit->clear();
            ui->lineEdit_2->clear();
            ret = msgBox.exec();
        }
        else{
            client_meno* temp = new client_meno();
            temp->show();
            connect(this, SIGNAL(sendUserName(QString)), temp, SLOT(getUserName(QString)));
            emit sendUserName(ui->lineEdit->text());
            close();
        }
    }

}


void MainWindow::on_pushButton_7_clicked()
{
    QProcess *process = new QProcess();

    if(!checker)
    {
        checker = true;
        QString path = "C:/Users/digitall home/Documents/Ap/alsa/python files";
        QString  command("python");
        QStringList params = QStringList() << "face_encoding.py";
        process->startDetached(command, params, path);
        process->waitForFinished();
        process->close();
    }

    else
    {
        checker = false;
        if(QFile::exists("C:/Users/digitall home/Documents/Ap/alsa/python files/face_encoding.py"))
        {
            Admin *d = new Admin;
            d->show();
            QFile file ("C:/Users/digitall home/Documents/Ap/alsa/python files/face_regression.txt");
            file.remove();

         }
  }
}


