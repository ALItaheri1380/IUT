#include "client_meno.h"
#include "ui_client_meno.h"
#include <QMessageBox>
#include <QFile>
#include "buylist.h"
#include "history.h"
#include "increase_funds.h"

client_meno::client_meno(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::client_meno)
{
    ui->setupUi(this);
    setWindowTitle("صفحه خریدار");
}

client_meno::~client_meno()
{
    delete ui;
}

void client_meno::on_pushButton_clicked()
{
    QFile file("prudoct.txt");
    int line_count = 0;
    QString line[100];
    QTextStream in(&file);

    file.open(QIODevice::ReadWrite);

    while( !in.atEnd())
    {
        line[line_count]=in.readLine();
        line_count++;
    }

    file.close();

    if(line_count == 0)
    {
        int ret;
              QMessageBox msgBox;
              msgBox.setText("هیچ کالایی موجود نیست !!!!!");
              ret = msgBox.exec();
        return;
    }

    list_pruduct* temp = new list_pruduct{};
    connect(this, SIGNAL(sendUserName(QString)), temp, SLOT(getUserName(QString)));

    temp->show();
    emit sendUserName(username);
}

void client_meno::on_pushButton_4_clicked()
{
    Increase_funds* temp = new Increase_funds{this};
    temp->show();
}

void client_meno::getUserName(QString str)
{
    username = str;
}

void client_meno::on_pushButton_3_clicked()
{
    int count = 0;

    QFile inputFile("buylist.txt");
    QStringList split;

    if (inputFile.open(QIODevice::ReadOnly))
    {
        QTextStream in(&inputFile);

        for (int i = 0; !in.atEnd(); i++)
        {
           QString line = in.readLine();
           split = line.split(",");

           if(split[1] == username)
           {
               count++;
           }
        }

        inputFile.close();
    }

    if(count == 0)
    {
        int ret;
        QMessageBox msgBox;
        msgBox.setText(" سبد خرید خالی  است!!!!!");
        ret = msgBox.exec();
        return;
    }

    buylist* temp = new buylist{this};
    connect(this, SIGNAL(sendPruductId(QString)), temp, SLOT(getsId(QString)));
    temp->show();
    emit sendPruductId(username);
}

void client_meno::on_pushButton_2_clicked()
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
        msgBox.setText(" تاریخچه تراکنش ها خالی است!!!!!");
        ret = msgBox.exec();
        return;
    }

    history* temp = new history{this};
    connect(this, SIGNAL(sendPruductId(QString)), temp, SLOT(getsId(QString)));
    temp->show();
    emit sendPruductId(username);
}

void client_meno::on_exit_clicked()
{
    int ret;
    QMessageBox msgBox;
    msgBox.setText(" خدانگهدار.");
    ret = msgBox.exec();
    close();
}
