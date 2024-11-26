#include "admin.h"
#include "ui_admin.h"
#include "Global.h"
#include "widget_user.h"
#include "edituser.h"
#include "add_to_cart.h"
#include "login.h"
#include "widget_transactions.h"
QVector<int> Admin::vec_id_kala;
Admin::Admin(int cons,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Admin)
{
    ui->setupUi(this);
    this->setFixedSize(1241,688);
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    setIndex_vector(cons);
    refresh();
}

Admin::~Admin()
{
    delete ui;
}

void Admin::show_item()
{
    if(ui->listWidget_user->count()>0)
    {
        ui->listWidget_user->clear();
    }
    for(int i=0;i<Global::vec_person.size();i++)
    {
        QListWidgetItem *m_ulitems = new QListWidgetItem;
        widget_user *m = new widget_user;
        m->set(Global::vec_person[i].get_user_name());
        ui->listWidget_user->addItem(m_ulitems);
        m_ulitems->setSizeHint(QSize(291,53));
        ui->listWidget_user->setItemWidget(m_ulitems,m);
    }
}

void Admin::refresh()
{
    Global::load_all();
    ui->listWidget_Transactions->clear();
    ui->listWidget_commodity->clear();
    ui->listWidget_user->clear();
    for(int i=0;i<Global::vec_person.size();i++)
    {
        QListWidgetItem *m_ulitems = new QListWidgetItem;
        widget_user *m = new widget_user;
        m->set(Global::vec_person[i].get_user_name());
        ui->listWidget_user->addItem(m_ulitems);
        m_ulitems->setSizeHint(QSize(291,53));
        ui->listWidget_user->setItemWidget(m_ulitems,m);
    }
    for(int i=0;i<Global::vec_article_cloths.size();i++)
    {
        vec_id_kala.push_back(Global::vec_article_cloths[i].get_id());
        QString o=Global::vec_article_cloths[i].get_name()+"\t\t"+Global::vec_article_cloths[i].get_seller_username();
        QListWidgetItem *m_ulitems = new QListWidgetItem(o);
        ui->listWidget_commodity->addItem(m_ulitems);
    }
    for(int i=0;i<Global::vec_article_sporting_goods.size();i++)
    {
        vec_id_kala.push_back(Global::vec_article_sporting_goods[i].get_id());
        QString o=Global::vec_article_sporting_goods[i].get_name()+"\t\t"+Global::vec_article_sporting_goods[i].get_seller_username();
        QListWidgetItem *m_ulitems = new QListWidgetItem(o);
        ui->listWidget_commodity->addItem(m_ulitems);
    }
    for(int i=0;i<Global::vec_tran.size();i++)
    {
        QListWidgetItem *m_ulitems = new QListWidgetItem;
        widget_transactions *m = new widget_transactions;
        m->set(Global::vec_tran[i].first.first,Global::vec_tran[i].first.second,Global::vec_tran[i].second.first , Global::vec_tran[i].second.second);
        ui->listWidget_Transactions->addItem(m_ulitems);
        m_ulitems->setSizeHint(QSize(420,109));
        ui->listWidget_Transactions->setItemWidget(m_ulitems,m);
    }
}


void Admin::on_listWidget_user_itemDoubleClicked(QListWidgetItem *item)
{
    int ind=ui->listWidget_user->currentRow();
    //EditUser
    EditUser *x = new EditUser(this);
    x->set(ind);
    x->setIndex_vector(index_vector);
    x->show();
    refresh();
}

void Admin::on_listWidget_commodity_itemDoubleClicked(QListWidgetItem *item)
{
    int ind=ui->listWidget_commodity->currentRow();
    add_to_cart *x=new add_to_cart;
    x->set(vec_id_kala[ind]);
    x->setIndex_vector(index_vector);
    x->admin();
    x->show();
    this->close();
}


void Admin::on_pushButton_log_out_clicked()
{
    this->close();
//    login *x=new login();

//    x->show();
}


void Admin::on_pushButton_clicked()
{
    refresh();
}

int Admin::getIndex_vector() const
{
    return index_vector;
}

void Admin::setIndex_vector(int newIndex_vector)
{
    index_vector = newIndex_vector;
}

