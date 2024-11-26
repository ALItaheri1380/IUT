#include "client.h"
#include "ui_client.h"
#include "login.h"
#include "cart.h"
#include<QChar>
#include "widget_kala.h"
#include "QListWidgetItem"
#include "add_to_cart.h"
#include "transaction.h"
#include "Global.h"
#include "QMovie"
QVector <int> Client::id[50];
Client::Client(int ind_cons,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Client)
{
    ui->setupUi(this);
    setIndex_vector(ind_cons);
    ui->label_price->setText(QString::number(Global::Active_person[index_vector].get_moneybags()));
    this->setFixedSize(1241,688);
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    QMovie* movie=new QMovie(":/new/prefix1/BitcoinAd.gif");
    ui->label_11->setMovie(movie);
    movie->start();
    refrsh();
}

void Client::serch(QString name, int min, int max, QString color, QString brand, QString weight, QString Qtype, QString gender)
{
    item_widget_cloths.clear();
    item_widget_sporting.clear();
    int min_weight;
    int max_weight;
    if(weight=="")
    {
        min_weight=0;
        max_weight=100000000;
    }
    else if (weight[0]=='0')
    {
        min_weight=0;
        max_weight=999;
    }
    else if(weight[0]=='1')
    {
        min_weight=1000;
        max_weight=4999;
    }
    else
    {
        min_weight=5000;
        max_weight=1000000;
    }
    if(Qtype.size()&&Qtype[0]=='C')
    {
        for(int i=0;i<Global::vec_article_cloths.size();i++)
        {
            cloths x=Global::vec_article_cloths[i];
            if ((x.get_name()==name || name.size()==0)&&(x.get_price()<=max &&x.get_price()>=min) && (x.get_color()==color || color.size()==0) && (x.get_brand_name()==brand || brand.size()==0) && (x.get_weight()>=min_weight && x.get_weight()<=max_weight)&& (x.get_gender()==gender || gender.size()==0))
            {
                item_widget_cloths.push_back(Global::vec_article_cloths[i]);
            }
        }
    }
    else if (Qtype.size()&&Qtype[0]=='E')
    {
        for(int i=0;i<Global::vec_article_sporting_goods.size();i++)
        {
            Sporting_goods x=Global::vec_article_sporting_goods[i];
            if ((x.get_name()==name || name.size()==0)&&(x.get_price()<=max &&x.get_price()>=min) && (x.get_color()==color || color.size()==0) && (x.get_brand_name()==brand || brand.size()==0) && (x.get_weight()>=min_weight && x.get_weight()<=max_weight))
            {
                item_widget_sporting.push_back(Global::vec_article_sporting_goods[i]);
            }
        }

    }
    else
    {
        for(int i=0;i<Global::vec_article_cloths.size();i++)
        {
            cloths x=Global::vec_article_cloths[i];
            bool t1=(x.get_name()==name || name.size()==0);
            bool t2=(x.get_price()<=max &&x.get_price()>=min);
            bool t3=(x.get_color()==color || color.size()==0);
            bool t4=(x.get_brand_name()==brand || brand.size()==0);
            bool t5=(x.get_weight()>=min_weight && x.get_weight()<=max_weight);
            bool t6=(x.get_gender()==gender || gender.size()==0);
            if (t1&&t2 && t3 && t4 && t5 && t6)
            {
                item_widget_cloths.push_back(Global::vec_article_cloths[i]);
            }
        }
        for(int i=0;i<Global::vec_article_sporting_goods.size();i++)
        {
            Sporting_goods x=Global::vec_article_sporting_goods[i];
            bool t1=(x.get_name()==name || name.size()==0);
            bool t2=(x.get_price()<=max &&x.get_price()>=min);
            bool t3=(x.get_color()==color || color.size()==0);
            bool t4=(x.get_brand_name()==brand || brand.size()==0);
            bool t5=(x.get_weight()>=min_weight && x.get_weight()<=max_weight);
            if (t1 && t2 && t3  && t4  && t5 )
            {
                item_widget_sporting.push_back(Global::vec_article_sporting_goods[i]);
            }
        }
    }

    show_item();

}

void Client::set()
{
    Name="";
    Min=0;
    Max=100000000;
    Color="";
    Brand="";
    Weight="";
    Type="";
    Gender="";
}

void Client::show_item()
{
    ui->label_price->setText(QString::number(Global::Active_person[index_vector].get_moneybags()));
    if(count!=0)
    {
        ui->listWidget_commodity->clear();
        count=0;
    }
    count=item_widget_cloths.size()+item_widget_sporting.size();
    id[index_vector].clear();
    if(count>0)
    {
        for(int i=0;i<item_widget_cloths.size();i++)
        {
           // t=1;
             QListWidgetItem *m_ulitems = new QListWidgetItem;
             widget_kala *m = new widget_kala;
             m->set(item_widget_cloths[i].get_image_file(),item_widget_cloths[i].get_name(),item_widget_cloths[i].get_color(),item_widget_cloths[i].get_price());
             ui->listWidget_commodity->addItem(m_ulitems);
             m_ulitems->setSizeHint(QSize(632,219));
             ui->listWidget_commodity->setItemWidget(m_ulitems,m);
             id[index_vector].push_back(item_widget_cloths[i].get_id());

        }
        for(int i=0;i<item_widget_sporting.size();i++)
        {

             //t=1;
            QListWidgetItem *m_ulitems = new QListWidgetItem;
            widget_kala *m =new widget_kala;
            m->set(item_widget_sporting[i].get_image_file(),item_widget_sporting[i].get_name(),item_widget_sporting[i].get_color(),item_widget_sporting[i].get_price());
            ui->listWidget_commodity->addItem(m_ulitems);
            m_ulitems->setSizeHint(QSize(632,219));
            ui->listWidget_commodity->setItemWidget(m_ulitems,m);
            id[index_vector].push_back(item_widget_sporting[i].get_id());
        }
    }
}


void Client::add_global_to_item_widget()
{
    item_widget_cloths.clear();
    item_widget_sporting.clear();
    for(int i=0;i<Global::vec_article_cloths.size();i++)
    {
        item_widget_cloths.push_back(Global::vec_article_cloths[i]);
    }
    for(int i=0;i<Global::vec_article_sporting_goods.size();i++)
    {
        item_widget_sporting.push_back(Global::vec_article_sporting_goods[i]);
    }
}

void Client::refrsh()
{
    Global::load_all();
    add_global_to_item_widget();
    show_item();

}

Client::~Client()
{
    delete ui;
}

void Client::on_pushButton_logout_clicked()
{
    //login *x=new login();
    this->close();
    //x->show();
}

void Client::on_pushButton_Cart_clicked()
{
    Cart *x=new Cart(index_vector,this);
    x->setIndex_vector(index_vector);
    this->close();
    x->show();
    ui->label_price->setText(QString::number(Global::Active_person[index_vector].get_moneybags()));
}

void Client::on_pushButton_moneybags_clicked()
{
    Transaction *x=new Transaction;
    x->setIndex_vector(index_vector);
    x->set();
    x->show();
    this->close();
    ui->label_price->setText(QString::number(Global::Active_person[index_vector].get_moneybags()));
}

void Client::on_pushButton_serch_clicked()
{
    Name=ui->lineEdit_serch->text();
    serch(Name,Min,Max,Color,Brand,Weight,Type,Gender);
}

//void Client::on_spinBox_max_editingFinished()
//{
//    Max=ui->spinBox_max->value();
//    serch(Name,Min,Max,Color,Brand,Weight,Type,Gender);
//}

//void Client::on_spinBox_min_editingFinished()
//{
//    Min=ui->spinBox_min->value();
//    serch(Name,Min,Max,Color,Brand,Weight,Type,Gender);
//}


void Client::on_listWidget_commodity_itemDoubleClicked(QListWidgetItem *item)
{
    int o=ui->listWidget_commodity->indexFromItem(item).row();
    add_to_cart *x=new add_to_cart;
    x->setIndex_vector(index_vector);
    x->set(id[index_vector][o]);
    x->show();
    this->close();
}




void Client::on_comboBox_coler_currentTextChanged(const QString &arg1)
{
    Color=arg1;
    serch(Name,Min,Max,Color,Brand,Weight,Type,Gender);
}


void Client::on_comboBox_brand_currentTextChanged(const QString &arg1)
{
    Brand=arg1;
    serch(Name,Min,Max,Color,Brand,Weight,Type,Gender);
}


void Client::on_comboBox_Weight_currentTextChanged(const QString &arg1)
{
    Weight = arg1;
    serch(Name,Min,Max,Color,Brand,Weight,Type,Gender);
}


void Client::on_comboBox_type_currentTextChanged(const QString &arg1)
{
    Type=arg1;
    serch(Name,Min,Max,Color,Brand,Weight,Type,Gender);
}


void Client::on_comboBox_sex_currentTextChanged(const QString &arg1)
{
    Gender=arg1;
    serch(Name,Min,Max,Color,Brand,Weight,Type,Gender);
}


void Client::on_spinBox_max_valueChanged(int arg1)
{
    Max=ui->spinBox_max->value();
    serch(Name,Min,Max,Color,Brand,Weight,Type,Gender);
}


void Client::on_spinBox_min_valueChanged(int arg1)
{
    Min=ui->spinBox_min->value();
    serch(Name,Min,Max,Color,Brand,Weight,Type,Gender);
}


void Client::on_pushButton_clicked()
{
    refrsh();
}

int Client::getIndex_vector() const
{
    return index_vector;
}

void Client::setIndex_vector(int newIndex_vector)
{
    index_vector = newIndex_vector;
}

