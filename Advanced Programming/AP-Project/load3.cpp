#include "load3.h"
#include "ui_load3.h"
#include<QMovie>
load3::load3(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::load3)
{
    this->setFixedSize(954,581);
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    ui->setupUi(this);
    QMovie* movie=new QMovie(":/new/prefix1/lod3.gif");
    ui->label->setMovie(movie);
    movie->start();
    timer1 = new QTimer (this);
    connect(timer1,SIGNAL(timeout()),this,SLOT(close_this()));
    timer1->start(80);
}

load3::~load3()
{
    delete ui;
}

void load3::close_this()
{
  Create_account *m=new Create_account;
  m->show();
  timer1->stop();
  this->close();
}
