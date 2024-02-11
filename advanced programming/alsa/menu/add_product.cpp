#include "add_product.h"
#include "ui_add_product.h"
#include <QFileDialog>
#include <QMessageBox>
#include "laptops.h"
#include "phones.h"
#include "watches.h"
#include "clothing.h"

Add_Product::Add_Product(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Add_Product)
{
    ui->setupUi(this);
    setWindowTitle("افزودن محصول");
}

Add_Product::~Add_Product()
{
    delete ui;
}

void Add_Product::on_pushButton_4_clicked()
{
    laptops* temp = new laptops{this};
    connect(this, SIGNAL(sendUserName(QString)), temp, SLOT(getUserName(QString)));

    temp->show();
    emit sendUserName(username);
}

void Add_Product::getUserName(QString str)
{
    username = str;
}

void Add_Product::on_pushButton_5_clicked()
{
    phones* temp = new phones{this};
    connect(this, SIGNAL(sendUserName(QString)), temp, SLOT(getUserName(QString)));

    temp->show();
    emit sendUserName(username);
}

void Add_Product::on_pushButton_2_clicked()
{
    watches* temp = new watches{this};
    connect(this, SIGNAL(sendUserName(QString)), temp, SLOT(getUserName(QString)));

    temp->show();
    emit sendUserName(username);
}

void Add_Product::on_pushButton_clicked()
{
    clothing* temp = new clothing{this};
    connect(this, SIGNAL(sendUserName(QString)), temp, SLOT(getUserName(QString)));

    temp->show();
    emit sendUserName(username);
}

void Add_Product::on_pushButton_3_clicked()
{
    close();
}
