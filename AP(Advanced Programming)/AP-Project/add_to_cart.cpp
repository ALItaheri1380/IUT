#include "add_to_cart.h"
#include "ui_add_to_cart.h"
#include<QMovie>
#include "Global.h"
#include "QMessageBox"
#include "client.h"
#include "admin.h"
add_to_cart::add_to_cart(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::add_to_cart),
    id{0}
{
     ui->setupUi(this);
     this->setFixedSize(1241,688);
     setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
     QMovie* movie=new QMovie(":/new/prefix1/iranserver.gif");
     QMovie* movie1=new QMovie(":/new/prefix1/XXwt.gif");
     ui->label_8->setMovie(movie);
     ui->label_9->setMovie(movie1);
     movie1->start();
     movie->start();
     ui->pushButton_4->hide();
}

add_to_cart::~add_to_cart()
{
    delete ui;
}

void add_to_cart::set(int id)
{
    this->id=id;
    ui->pushButton->show();
    ui->pushButton_2->show();
    if(Global::serch_id_cloths(id)!=-1)
    {
        int index=Global::serch_id_cloths(id);
        ui->label_name->setText(Global::vec_article_cloths[index].get_name());
        ui->label_price->setText(QString::number(Global::vec_article_cloths[index].get_price()));
        ui->label_seller->setText(Global::vec_article_cloths[index].get_seller_username());
        ui->label_weight->setText(QString::number(Global::vec_article_cloths[index].get_weight()));
        ui->label_type->setText("cloths");
        ui->label_coler->setText(Global::vec_article_cloths[index].get_color());
        ui->label_brand->setText(Global::vec_article_cloths[index].get_brand_name());
        ui->label_other->setText(Global::vec_article_cloths[index].get_gender());
        QString file=Global::vec_article_cloths[index].get_image_file();
        QString x="QWidget {background-image: url("+file+") ;}";
        ui->widget->setStyleSheet(x);
        ui->spinBox->setMaximum(Global::vec_article_cloths[index].get_stock());
    }
    else if(Global::serch_id_sporting_goods(id)!=-1)
    {
        int index=Global::serch_id_sporting_goods(id);
        ui->label_name->setText(Global::vec_article_sporting_goods[index].get_name());
        ui->label_price->setText(QString::number(Global::vec_article_sporting_goods[index].get_price()));
        ui->label_seller->setText(Global::vec_article_sporting_goods[index].get_seller_username());
        ui->label_weight->setText(QString::number(Global::vec_article_sporting_goods[index].get_weight()));
        ui->label_type->setText("sporting_goods");
        ui->label_coler->setText(Global::vec_article_sporting_goods[index].get_color());
        ui->label_brand->setText(Global::vec_article_sporting_goods[index].get_brand_name());
        ui->label_other->setText(Global::vec_article_sporting_goods[index].get_material());
        QString file=Global::vec_article_sporting_goods[index].get_image_file();
        QString x="QWidget {background-image: url("+file+") ;}";
        ui->widget->setStyleSheet(x);
        ui->spinBox->setMaximum(Global::vec_article_sporting_goods[index].get_stock());
    }
}

void add_to_cart::admin()
{
    ui->pushButton_4->show();
    ui->pushButton->hide();
    ui->pushButton_2->hide();
    ui->spinBox->hide();
}

void add_to_cart::on_pushButton_clicked()
{
    Global::load_all();
    if(Global::serch_id_cloths(id)!=-1&&(Global::vec_article_cloths[Global::serch_id_cloths(id)].get_stock()<ui->spinBox->value()))
    {
       QMessageBox *x=new QMessageBox;
       x->setText("not in stock");
       x->exec();
    }
    else if(Global::serch_id_sporting_goods(id)!=-1 && (Global::vec_article_sporting_goods[Global::serch_id_sporting_goods(id)].get_stock()<ui->spinBox->value()))
    {
        QMessageBox *x=new QMessageBox;
        x->setText("not in stock");
        x->exec();
    }
    else if(Global::serch_id_cloths(id)!=-1)
    {
        Global::Shopping_cart[index_vector].push_back(qMakePair(id , ui->spinBox->value()));
        Global::vec_article_cloths[Global::serch_id_cloths(id)].set_stock(Global::vec_article_cloths[Global::serch_id_cloths(id)].get_stock()-ui->spinBox->value());
        QMessageBox *x=new QMessageBox;
        x->setText("added");
        x->exec();
    }
    else if(Global::serch_id_sporting_goods(id)!=-1)
    {
        Global::Shopping_cart[index_vector].push_back(qMakePair(id , ui->spinBox->value()));
        Global::vec_article_sporting_goods[Global::serch_id_sporting_goods(id)].set_stock(Global::vec_article_sporting_goods[Global::serch_id_sporting_goods(id)].get_stock()-ui->spinBox->value());
        QMessageBox *x=new QMessageBox;
        x->setText("added");
        x->exec();

    }
    Global::save_all();
    std::string x;
   x="save_"+Global::Active_person[index_vector].get_user_name().toStdString()+".txt";
   std::fstream out(x , std::ios::out);
   for (int i=0;i<Global::Shopping_cart[index_vector].size() ; i++)
   {
       out<<Global::Shopping_cart[index_vector][i].first<<"\n"
         <<Global::Shopping_cart[index_vector][i].second<<"\n";

   }
   out.close();
    this->close();
    Client *y= new Client(index_vector);
    y->setIndex_vector(index_vector);
    y->show();

}



void add_to_cart::on_pushButton_2_clicked()
{
    this->close();
    Client *y= new Client(index_vector);
    y->setIndex_vector(index_vector);
    y->show();
}


void add_to_cart::on_pushButton_4_clicked()
{
    Admin *x=new Admin(index_vector);
    x->show();
    x->setIndex_vector(index_vector);
    this->close();
}

int add_to_cart::getIndex_vector() const
{
    return index_vector;
}

void add_to_cart::setIndex_vector(int newIndex_vector)
{
    index_vector = newIndex_vector;
}

