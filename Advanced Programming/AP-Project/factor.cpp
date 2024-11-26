#include "factor.h"
#include "ui_factor.h"
#include "Global.h"
factor::factor(int inn,QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::factor)
{
    ui->setupUi(this);
    this->setFixedSize(687,721);
    ui->dockWidgetContents->setWindowTitle("Factor");
    setIndex_vector(inn);
    for(int i=0;i<Global::vec_of_Buyer.size();i++)
    {
        if(Global::serch_id_cloths(Global::vec_of_Buyer[i].second.first.first)!=-1)
        {
            if(Global::vec_article_cloths[Global::serch_id_cloths(Global::vec_of_Buyer[i].second.first.first)].get_seller_username()==Global::Active_person[index_vector].get_user_name())
            {
                ind.push_back(i);
            }
        }
        else if(Global::serch_id_sporting_goods(Global::vec_of_Buyer[i].second.first.first)!=-1)
        {
            int inde=Global::serch_id_sporting_goods(Global::vec_of_Buyer[i].second.first.first);
            if(Global::vec_article_sporting_goods[inde].get_seller_username()==Global::Active_person[index_vector].get_user_name())
            {
                ind.push_back(i);
            }
        }
    }
    show_item(0);
}

factor::~factor()
{
    delete ui;
}

void factor::show_item(int index)
{
    if(index<0||index>=ind.size())
    {
        if(index<0)
            index=0;
        else
            index=ind.size()-1;
    }
    if(Global::vec_of_Buyer.size()!=0)
    {

        ui->label_time->setText(Global::vec_of_Buyer[ind[index]].second.second.first);
        ui->label_name->setText(Global::vec_of_Buyer[ind[index]].second.first.second);
        if(Global::serch_id_cloths(Global::vec_of_Buyer[ind[index]].second.first.first)!=-1)
        {
            ui->label_item->setText(Global::vec_article_cloths[Global::serch_id_cloths(Global::vec_of_Buyer[ind[index]].second.first.first)].get_name());
        }
        else
        {
            ui->label_item->setText(Global::vec_article_sporting_goods[Global::serch_id_sporting_goods(Global::vec_of_Buyer[ind[index]].second.first.first)].get_name());
        }
        ui->label_Quantiy->setText(QString::number(Global::vec_of_Buyer[ind[index]].first));
        ui->label_price->setText(QString::number(Global::vec_of_Buyer[ind[index]].second.second.second));
        ui->label_total->setText(QString::number(Global::vec_of_Buyer[ind[index]].first*Global::vec_of_Buyer[ind[index]].second.second.second));
    }
}


void factor::on_pushButton_next_clicked()
{
    show_item(++now);
}


void factor::on_pushButton_previous_clicked()
{
    show_item(--now);
}

int factor::getIndex_vector() const
{
    return index_vector;
}

void factor::setIndex_vector(int newIndex_vector)
{
    index_vector = newIndex_vector;
}

