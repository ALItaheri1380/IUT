#include "widget_show_kala_customer.h"
#include "ui_widget_show_kala_customer.h"
#include "Global.h"
#include "customer.h"
widget_show_kala_customer::widget_show_kala_customer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::widget_show_kala_customer)
{
    ui->setupUi(this);
}

widget_show_kala_customer::~widget_show_kala_customer()
{
    delete ui;
}

void widget_show_kala_customer::set(int id, QString file,QString Name,QString color, int price, int number)
{
    this->file=file;
    this->Name=Name;
    this->id=id;
    this->color=color;
    this->price=price;
    this->number=number;
    QString x="QWidget {background-image: url("+file+") ;}";
    ui->widget->setStyleSheet(x);
    ui->lineEdit_name->setText(Name);
    ui->lineEdit_color->setText(color);
    ui->lineEdit_price->setText(QString::fromStdString(std::to_string(price)));
    ui->spinBox->setValue(number);
}

void widget_show_kala_customer::on_spinBox_valueChanged(int arg1)
{
    int ind = Global::serch_id_cloths(id);
    if(ind!=-1)
    {
        Global::vec_article_cloths[ind].set_stock(arg1);
        for (int i=0;i<customer::vec_cloths[index_vector].size();i++)
        {
            if (id == customer::vec_cloths[index_vector][i].get_id())
            {
                customer::vec_cloths[index_vector][i].set_stock(arg1);
            }
        }
    }
    else
    {
        ind=Global::serch_id_sporting_goods(id);
        Global::vec_article_sporting_goods[ind].set_stock(arg1);
        for (int i=0;i<customer::vec_sporting[index_vector].size();i++)
        {
            if (id == customer::vec_sporting[index_vector][i].get_id())
            {
                customer::vec_sporting[index_vector][i].set_stock(arg1);
            }
        }
    }
    Global::save_article();
}


void widget_show_kala_customer::on_pushButton_change_clicked()
{
    file= QFileDialog::getOpenFileName(this,"open",QDir::homePath());
    QString x="QWidget {background-image: url("+file+") ;}";
    ui->widget->setStyleSheet(x);
    int ind = Global::serch_id_cloths(id);
    if(ind!=-1)
    {
        Global::vec_article_cloths[ind].setImage_File(file);
        for (int i=0;i<customer::vec_cloths[index_vector].size();i++)
        {
            if (id == customer::vec_cloths[index_vector][i].get_id())
            {
                customer::vec_cloths[index_vector][i].setImage_File(file);
            }
        }
    }
    else
    {
        ind=Global::serch_id_sporting_goods(id);
        Global::vec_article_sporting_goods[ind].setImage_File(file);
        for (int i=0;i<customer::vec_sporting[index_vector].size();i++)
        {
            if (id == customer::vec_sporting[index_vector][i].get_id())
            {
                customer::vec_sporting[index_vector][i].setImage_File(file);
            }
        }
    }
    Global::save_article();
}


void widget_show_kala_customer::on_lineEdit_price_editingFinished()
{
    int n=ui->lineEdit_price->text().toInt();
    int ind = Global::serch_id_cloths(id);
    if(ind!=-1)
    {
        Global::vec_article_cloths[ind].set_Price(n);
        for (int i=0;i<customer::vec_cloths[index_vector].size();i++)
        {
            if (id == customer::vec_cloths[index_vector][i].get_id())
            {
                customer::vec_cloths[index_vector][i].set_Price(n);
            }
        }
    }
    else
    {
        ind=Global::serch_id_sporting_goods(id);
        Global::vec_article_sporting_goods[ind].set_Price(n);
        for (int i=0;i<customer::vec_sporting[index_vector].size();i++)
        {
            if (id == customer::vec_sporting[index_vector][i].get_id())
            {
                customer::vec_sporting[index_vector][i].set_Price(n);
            }
        }
    }
    Global::save_article();
}

int widget_show_kala_customer::getIndex_vector() const
{
    return index_vector;
}

void widget_show_kala_customer::setIndex_vector(int newIndex_vector)
{
    index_vector = newIndex_vector;
}

