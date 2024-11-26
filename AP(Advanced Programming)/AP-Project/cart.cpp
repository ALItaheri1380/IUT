#include "cart.h"
#include "ui_cart.h"
#include "client.h"
#include "Global.h"
#include "QListWidgetItem"
#include "widget_kala.h"
#include "QMessageBox"
#include "transaction.h"
#include <iostream>
Cart::Cart(int cons,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Cart)
{
    ui->setupUi(this);
    this->setFixedSize(1241,688);
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    setIndex_vector(cons);
    show_item();
}

void Cart::show_item()
{
    if(ui->listWidget->count()>0)
        ui->listWidget->clear();
    for(int i=0;i<Global::Shopping_cart[index_vector].size();i++)
    {
       // t=1;

         int id=Global::Shopping_cart[index_vector][i].first;
         if (Global::serch_id_cloths(id)!=-1)
         {
             int index=Global::serch_id_cloths(id);
             QListWidgetItem *m_ulitems = new QListWidgetItem;
             widget_kala *m = new widget_kala;
             m->set(Global::vec_article_cloths[index].get_image_file() ,Global::vec_article_cloths[index].get_name(),Global::vec_article_cloths[index].get_color(),Global::vec_article_cloths[index].get_price());
             ui->listWidget->addItem(m_ulitems);
             m_ulitems->setSizeHint(QSize(632,219));
             ui->listWidget->setItemWidget(m_ulitems,m);
             sum+=Global::vec_article_cloths[index].get_price()*Global::Shopping_cart[index_vector][i].second;
         }
         else
         {
             int index=Global::serch_id_sporting_goods(id);
             QListWidgetItem *m_ulitems = new QListWidgetItem;
             widget_kala *m = new widget_kala;
             m->set(Global::vec_article_sporting_goods[index].get_image_file() ,Global::vec_article_sporting_goods[index].get_name(),Global::vec_article_sporting_goods[index].get_color(),Global::vec_article_sporting_goods[index].get_price());
             ui->listWidget->addItem(m_ulitems);
             m_ulitems->setSizeHint(QSize(632,219));
             ui->listWidget->setItemWidget(m_ulitems,m);
             sum+=Global::vec_article_sporting_goods[index].get_price()*Global::Shopping_cart[index_vector][i].second;
         }
    }
    ui->lineEdit_pice->setText(QString::number(sum));
}

int Cart::getIndex_vector() const
{
    return index_vector;
}

void Cart::setIndex_vector(int newIndex_vector)
{
    index_vector = newIndex_vector;
}

Cart::~Cart()
{
    delete ui;
}

void Cart::on_pushButton_close_clicked()
{
    Client* x=new Client(index_vector,this);
    this->close();
    x->setIndex_vector(index_vector);
    x->show();
}


void Cart::on_pushButton_romove_clicked()
{
     int i=ui->listWidget->currentRow();
     int id = Global::Shopping_cart[index_vector][i].first;
     int ted=Global::Shopping_cart[index_vector][i].second;
     Global::Shopping_cart[index_vector].remove(i);
     std::string x;
     x="save_"+Global::Active_person[index_vector].get_user_name().toStdString()+".txt";
     std::fstream out(x , std::ios::out);
     for (int i=0;i<Global::Shopping_cart[index_vector].size() ; i++)
     {
         out<<Global::Shopping_cart[index_vector][i].first<<"\n"
           <<Global::Shopping_cart[index_vector][i].second<<"\n";

     }
     out.close();
     QListWidgetItem *m=ui->listWidget->currentItem();
     ui->listWidget->removeItemWidget(m);
     delete m;
     if (Global::serch_id_cloths(id)!=-1)
     {
         int index=Global::serch_id_cloths(id);
         sum-=Global::vec_article_cloths[index].get_price()*ted;
     }
     else
     {
         int index=Global::serch_id_sporting_goods(id);
         sum-=Global::vec_article_sporting_goods[index].get_price()*ted;
     }
     ui->lineEdit_pice->text().clear();
     ui->lineEdit_pice->setText(QString::number(sum));
}


void Cart::on_pushButton_buy_clicked()
{
    QDate cd = QDate::currentDate();
    QTime ct = QTime::currentTime();
    QString now=cd.toString()+"\t"+ct.toString();
    if (Global::Active_person[index_vector].get_moneybags()>=sum)
    {
        Global::Active_person[index_vector].setMoneybags(Global::Active_person[index_vector].get_moneybags()-sum);
        for(int i=0 ; i<Global::vec_person.size();i++)
        {
            if(Global::vec_person[i].get_user_name()==Global::Active_person[index_vector].get_user_name())
            {
                Global::vec_person[i].setMoneybags(Global::Active_person[index_vector].get_moneybags());
            }
        }
        for(int i=0;i<Global::Shopping_cart[index_vector].size();i++)
        {
            int id = Global::Shopping_cart[index_vector][i].first;
            int ind=Global::serch_id_cloths(id);
            if (ind>=0)
            {
                Global::vec_article_cloths[ind].set_number_sold(Global::vec_article_cloths[ind].get_number_sold()+Global::Shopping_cart[index_vector][i].second);
                QString user=Global::vec_article_cloths[ind].get_seller_username();
                for(int j=0;j<Global::vec_person.size();j++)
                {
                    if(user==Global::vec_person[j].get_user_name())
                    {
                        Global::vec_person[j].setMoneybags(Global::vec_person[j].get_moneybags()+Global::vec_article_cloths[ind].get_price()*Global::Shopping_cart[index_vector][i].second);
                    }
                }
                Global::vec_of_Buyer.push_back(qMakePair(Global::Shopping_cart[index_vector][i].second,qMakePair(qMakePair(Global::Shopping_cart[index_vector][i].first,Global::Active_person[index_vector].get_user_name()),qMakePair(now,Global::vec_article_cloths[ind].get_price()))));
            }
            else
            {
                Global::vec_article_sporting_goods[ind].set_number_sold(Global::vec_article_sporting_goods[ind].get_number_sold()+Global::Shopping_cart[index_vector][i].second);
                QString user=Global::vec_article_sporting_goods[ind].get_seller_username();
                for(int j=0;j<Global::vec_person.size();j++)
                {
                    if(user==Global::vec_person[j].get_user_name())
                    {
                        Global::vec_person[j].setMoneybags(Global::vec_person[j].get_moneybags()+Global::vec_article_sporting_goods[ind].get_price()*Global::Shopping_cart[index_vector][i].second);
                    }
                }
                Global::vec_of_Buyer.push_back(qMakePair(Global::Shopping_cart[index_vector][i].second,qMakePair(qMakePair(Global::Shopping_cart[index_vector][i].first,Global::Active_person[index_vector].get_user_name()),qMakePair(now,Global::vec_article_sporting_goods[ind].get_price()))));
            }
        }
        Global::save();
        Global::save_article();
        Global::save_buyer();

        QMessageBox *xx=new QMessageBox;
        xx->setText("paid with money bags");
        xx->exec();
        Global::vec_tran.push_back(qMakePair(qMakePair(ui->lineEdit_pice->text().toInt(),Global::Active_person[index_vector].get_user_name()),qMakePair("buy",now) ));
        for(int i=0;i<Global::Shopping_cart[index_vector].size();i++)
        {
            if(Global::serch_id_cloths(Global::Shopping_cart[index_vector][i].first)!=-1)
                Global::vec_tran.push_back(qMakePair(qMakePair(Global::vec_article_cloths[Global::serch_id_cloths( Global::Shopping_cart[index_vector][i].first)].get_price()*Global::Shopping_cart[index_vector][i].second, Global::vec_article_cloths[Global::serch_id_cloths(Global::Shopping_cart[index_vector][i].first)].get_seller_username()),qMakePair("sell",now) ));
            else if(Global::serch_id_sporting_goods(Global::Shopping_cart[index_vector][i].first)!=-1)
            {
                Global::vec_tran.push_back(qMakePair(qMakePair(Global::vec_article_sporting_goods[Global::serch_id_sporting_goods(Global::Shopping_cart[index_vector][i].first)].get_price()*Global::Shopping_cart[index_vector][i].second, Global::vec_article_sporting_goods[Global::serch_id_sporting_goods(Global::Shopping_cart[index_vector][i].first)].get_seller_username()),qMakePair("sell",now) ));
            }
        }
        Global::Shopping_cart[index_vector].clear();
        this->close();
        Client *xo=new Client(index_vector);
        xo->show();
    } 
    else
    {
        QMessageBox *qm = new QMessageBox(this);
        qm->setText("Top up your wallet first");
        qm->setStyleSheet("QMessageBox{background: rgb(255,255,255);}");
        qm->exec();
        this->close();
        Client *xo=new Client(index_vector);
        xo->show();
    }


}

