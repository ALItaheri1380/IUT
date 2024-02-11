#include "custumer_menu.h"
#include "ui_custumer_menu.h"
#include "add_product.h"
#include <QMessageBox>
#include "list_pruduct.h"
#include "history.h"
#include <QFile>
#include <QDir>

custumer_menu::custumer_menu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::custumer_menu)
{

}

custumer_menu::~custumer_menu()
{
    delete ui;
}

void custumer_menu::on_pushButton_2_clicked()
{    
    Add_Product* temp = new Add_Product{this};
    connect(this, SIGNAL(sendUserName(QString)), temp, SLOT(getUserName(QString)));

    temp->show();
    emit sendUserName(username);
}

void custumer_menu::getUserName(QString str)
{
    QFile myfile("Login_customer.txt");
    if(!myfile.open(QFile::ReadOnly |QFile::Text))
    {
       return;
    }

    QTextStream  in(&myfile);
    while (!in.atEnd())
    {
        QString myText = in.readLine();
        QStringList List = myText.split(',');
        if(str == List[1])
        {
            username = List[0];
            break;
        }
    }

    ui->setupUi(this);
    setWindowTitle("صفحه فروشنده");
}

void custumer_menu::on_pushButton_clicked()
{
    list_pruduct* temp = new list_pruduct{};
    connect(this, SIGNAL(sendUserName(QString)), temp, SLOT(getUserName(QString)));

    temp->show();
    emit sendUserName(username);
}

void custumer_menu::on_pushButton_3_clicked()
{
    QFile file("history.txt");
    int line_count = 0;
    QString line;
    QTextStream in(&file);

    file.open(QIODevice::ReadWrite);

    while( !in.atEnd())
    {
        line=in.readLine();

        QStringList split = line.split(",");

        if(split[0] == username || split[1] == username)
        {
            line_count++;
        }
    }

    file.close();

    if(line_count == 0)
    {
              int ret;
              QMessageBox msgBox;
              msgBox.setText("تاریخچه تراکنش ها خالی است !!!!!");
              ret = msgBox.exec();
              return;
    }

    history* temp = new history{this};
    connect(this, SIGNAL(sendUserName(QString)), temp, SLOT(getsId(QString)));
    temp->show();
    emit sendUserName(username);
}

void custumer_menu::on_pushButton_4_clicked()
{
    int ret;
    QMessageBox msgBox;
    msgBox.setText("خدانگهدار");
    ret = msgBox.exec();
    close();
     return;
}

