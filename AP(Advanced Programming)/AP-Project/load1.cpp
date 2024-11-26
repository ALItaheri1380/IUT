#include "load1.h"
#include "ui_load1.h"
#include"login.h"
#include "article.h"
QVector <Person>Global::vec_person;
Person Global::Active_person[20];
QVector <cloths>Global::vec_article_cloths;
QVector <QPair <int ,QPair<QPair<int,QString> , QPair<QString , int>>>> Global::vec_of_Buyer;
QVector<Sporting_goods> Global::vec_article_sporting_goods;
QVector<QPair<int , int > > Global::Shopping_cart[20];
load1::load1(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::load1)
{
    ui->setupUi(this);
    this->setFixedSize(519,568);
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    timer1 = new QTimer (this);
    timer2 = new QTimer (this);
    connect(timer1,SIGNAL(timeout()),this,SLOT(updat()));
    timer1->start(80);
    connect(timer2,SIGNAL(timeout()),this,SLOT(close_this()));
    timer2->start(8000);
}


load1::~load1()
{
    delete ui;
}

void load1::close_this()
{
    login* m = new login;
    m->show();
    timer2->stop();
    this->close();
}

void load1::updat()
{
   ui->progressBar->setValue(ui->progressBar->value()+1);
}
