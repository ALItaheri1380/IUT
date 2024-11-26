#include "widget_kala.h"
#include "ui_widget_kala.h"

widget_kala::widget_kala(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::widget_kala)
{
    ui->setupUi(this);
}

widget_kala::~widget_kala()
{
    delete ui;
}

void widget_kala::set(QString phonto, QString name, QString color, int price)
{
    ui->label_name->setText(name);
    ui->label_price->setText(QString::number(price));
    QString x="QWidget {background-image: url("+phonto+") ;}";
    ui->frame->setStyleSheet(x);
    if(color=="Red")
    {
        ui->lineEdit_coler->setStyleSheet("background: rgb(255,0,0);");
    }
    else if(color=="Blue")
    {
        ui->lineEdit_coler->setStyleSheet("background: rgb(0,0,255);");
    }
    else if(color=="Yellow")
    {
        ui->lineEdit_coler->setStyleSheet("background: rgb(255,255,0);");
    }
    else
        ui->lineEdit_coler->hide();


}

int widget_kala::getIndex_vector() const
{
    return index_vector;
}

void widget_kala::setIndex_vector(int newIndex_vector)
{
    index_vector = newIndex_vector;
}
