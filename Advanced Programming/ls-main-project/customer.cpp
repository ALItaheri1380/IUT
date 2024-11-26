#include "customer.h"
#include "ui_customer.h"
#include "add_kala.h"
#include "login.h"
#include "widget_show_kala_customer.h"
#include "QListWidgetItem"
#include "factor.h"
#include "transaction_customer.h"
#include <QTime>
#include <QDate>
#include "windows.h"
QVector<cloths> customer::vec_cloths[50];
QVector<Sporting_goods> customer::vec_sporting[50];
QVector <int> customer::id[50];
int customer::size_of_widget=0;
customer::customer(int inn,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::customer)
{

    ui->setupUi(this);
    this->setFixedSize(1241,688);
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    setIndex_vector(inn);

    refresh();

}

customer::~customer()
{
    delete ui;
}

void customer::on_pushButton_add_clicked()
{
    add_kala *x=new add_kala(this);
    x->setIndex_vector(index_vector);
    this->close();
    x->show();
}


void customer::on_pushButton_4_clicked()
{
    int index=ui->listWidget->currentRow();
    if (index!=-1)
    {
        for(int i=0;i<vec_cloths[index_vector].size();i++)
        {
            if(vec_cloths[index_vector][i].get_id()==id[index_vector][index])
            {
                vec_cloths[index_vector].remove(i);
                int ind=Global::serch_id_cloths(id[index_vector][index]);
                if (ind>=0)
                    Global::vec_article_cloths.remove(ind);
                break;
            }
        }
        for(int i=0;i<vec_sporting[index_vector].size();i++)
        {
            if (vec_sporting[index_vector][i].get_id()==id[index_vector][index])
            {
                vec_sporting[index_vector].remove(i);
                break;
                int ind=Global::serch_id_sporting_goods(id[index_vector][index]);
                if (ind>=0)
                    Global::vec_article_sporting_goods.remove(ind);
            }
        }
        Global::save_article();
        show_item();
    }
}


void customer::on_pushButton_logout_clicked()
{
    this->close();
    delete this;
}

int customer::getSize_of_widget() const
{
    return size_of_widget;
}

void customer::setSize_of_widget(int newSize_of_widget)
{
    size_of_widget = newSize_of_widget;
}

void customer::show_item()
{
    ui->label_mooney->setText(QString::number(Global::Active_person[index_vector].get_moneybags()));
    if(size_of_widget!=0)
    {
        ui->listWidget->clear();
        size_of_widget=0;
        id[index_vector].clear();
    }
    size_of_widget=vec_cloths[index_vector].size()+vec_sporting[index_vector].size();
    if(size_of_widget>0)
    {
        for(int i=0;i<vec_cloths[index_vector].size();i++)
        {
             QListWidgetItem *m_ulitems = new QListWidgetItem;
             widget_show_kala_customer *m = new widget_show_kala_customer;
             m->setIndex_vector(index_vector);
             int idd=vec_cloths[index_vector][i].get_id();
             QString f=vec_cloths[index_vector][i].get_image_file();
             QString n=vec_cloths[index_vector][i].get_name();
             QString c=vec_cloths[index_vector][i].get_color();
             int p=vec_cloths[index_vector][i].get_price();
             int ss=vec_cloths[index_vector][i].get_stock();
             m->set(idd,f,n,c,p,ss);
             ui->listWidget->addItem(m_ulitems);
             m_ulitems->setSizeHint(QSize(1031,218));
             ui->listWidget->setItemWidget(m_ulitems,m);
             id[index_vector].push_back(vec_cloths[index_vector][i].get_id());

        }
        for(int i=0;i<vec_sporting[index_vector].size();i++)
        {
            QListWidgetItem *m_ulitems = new QListWidgetItem;
            widget_show_kala_customer *m = new widget_show_kala_customer;
            m->setIndex_vector(index_vector);
            m->set(vec_sporting[index_vector][i].get_id(),vec_sporting[index_vector][i].get_image_file(),vec_sporting[index_vector][i].get_name(),vec_sporting[index_vector][i].get_color(),vec_sporting[index_vector][i].get_price(),vec_sporting[index_vector][i].get_stock());
            ui->listWidget->addItem(m_ulitems);
            m_ulitems->setSizeHint(QSize(1031,218));
            ui->listWidget->setItemWidget(m_ulitems,m);
            id[index_vector].push_back(vec_sporting[index_vector][i].get_id());
        }
    }
}

void customer::refresh()
{
    Global::load_all();
    for(int i=0;i<Global::vec_person.size();i++)
    {
        if(Global::vec_person[i].get_user_name()==Global::Active_person[index_vector].get_user_name())
        {
            Global::Active_person[index_vector]=Global::vec_person[i];
        }
    }
    ui->label_mooney->setText(QString::number(Global::Active_person[index_vector].get_moneybags()));
    if (vec_cloths[index_vector].size()>0)
           vec_cloths[index_vector].clear();
    if (vec_sporting[index_vector].size()>0)
            vec_sporting[index_vector].clear();
    for (int i=0;i<Global::vec_article_cloths.size();i++)
    {
        QString o=Global::vec_article_cloths[i].get_seller_username();
        QString o1=Global::Active_person[index_vector].get_user_name();
        if (o==o1)
        {
            vec_cloths[index_vector].push_back(Global::vec_article_cloths[i]);
        }
    }
    for (int i=0;i<Global::vec_article_sporting_goods.size();i++)
    {
        QString o=Global::vec_article_sporting_goods[i].get_seller_username();
        QString o1=Global::Active_person[index_vector].get_user_name();
        if (o==o1)
        {
            vec_sporting[index_vector].push_back(Global::vec_article_sporting_goods[i]);

        }
    }
    show_item();
}




void customer::on_pushButton_3_clicked()
{
    factor *f=new factor(index_vector);
    f->setIndex_vector(index_vector);
    f->show();
}


void customer::on_pushButton_clicked()
{
    transaction_customer *x=new transaction_customer;
    x->setIndex_vector(index_vector);
    connect(x,SIGNAL(accept_item(int)),this,SLOT(check(int)));
    x->show();
}


void customer::on_pushButton_2_clicked()
{
    refresh();
}

void customer::check(int l)
{
    if(l==1)
    {
        QDate cd = QDate::currentDate();
        QTime ct = QTime::currentTime();
        QString now=cd.toString()+"\t"+ct.toString();
        Global::vec_tran.push_back(qMakePair(qMakePair(ui->label_mooney->text().toInt(),Global::Active_person[index_vector].get_user_name()),qMakePair("withdraw moneybags",now) ));
        Global::buy=0;
        Global::Active_person[index_vector].setMoneybags(0);
        for(int i=0;i<Global::vec_person.size();i++)
        {
            if(Global::Active_person[index_vector].get_user_name()==Global::vec_person[i].get_user_name())
            {
                Global::vec_person[i].setMoneybags(0);

            }
        }
        Global::save();
        Global::save_all();
        ui->label_mooney->setText(QString::number(Global::Active_person[index_vector].get_moneybags()));
    }
}

int customer::getIndex_vector() const
{
    return index_vector;
}

void customer::setIndex_vector(int newIndex_vector)
{
    index_vector = newIndex_vector;
}

