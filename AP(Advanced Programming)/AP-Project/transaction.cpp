#include "transaction.h"
#include "ui_transaction.h"
#include "random"
#include "qmessagebox.h"
#include "Global.h"
#include <QTextStream>
#include "client.h"
Transaction::Transaction(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Transaction)
{
    ui->setupUi(this);
    this->setFixedSize(958,479);
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    ui->pushButton_password->hide();
    ui->lineEdit_pssword->hide();
}

Transaction::~Transaction()
{
    delete ui;
}

void Transaction::on_pushButton_password_clicked()
{
    pass=rand()%1000000;
    QMessageBox *x=new QMessageBox;
    x->setText(QString::number(pass));
    x->exec();
}

void Transaction::set(int p)
{
    if (p==0)
    {
        ui->label_seller->setText("charge moneybags");
        ui->label_name->setText(Global::Active_person[index_vector].get_name());
        ui->label_phone->setText(Global::Active_person[index_vector].get_phone_number());
        ui->lineEdit_price->setReadOnly(0);
    }
    else
    {
        ui->label_seller->setText("buyer information");
        ui->label_name->setText(Global::Active_person[index_vector].get_name());
        ui->label_phone->setText(Global::Active_person[index_vector].get_phone_number());
        ui->lineEdit_price->setText(QString::number(p));
        ui->lineEdit_price->setReadOnly(1);

    }
}


void Transaction::on_pushButton_payment_clicked()
{
    if(ui->lineEdit_card->text().isEmpty() || ui->lineEdit_cvv2->text().isEmpty() || ui->lineEdit_month->text().isEmpty() || ui->lineEdit_pssword->text().isEmpty() || ui->lineEdit_year->text().isEmpty())
    {
        QMessageBox *qm = new QMessageBox(this);
        qm->setText("Fill all the fields");
        qm->exec();
    }
    else
    {
        QDate cd = QDate::currentDate();
        QTime ct = QTime::currentTime();
        QString now=cd.toString()+"\t"+ct.toString();
        if(ui->label_seller->text()=="charge moneybags")
        {
            if(ui->lineEdit_pssword->text().toInt()==pass)
            {
                Global::vec_tran.push_back(qMakePair(qMakePair(ui->lineEdit_price->text().toInt(),Global::Active_person[index_vector].get_user_name()),qMakePair("charge moneybags",now) ));
                for(int i=0;i<Global::vec_person.size();i++)
                {
                    if(Global::vec_person[i].get_user_name()==Global::Active_person[index_vector].get_user_name())
                    {
                        Global::Active_person[index_vector].setMoneybags(Global::Active_person[index_vector].get_moneybags()+ui->lineEdit_price->text().toInt());
                        Global::vec_person[i].setMoneybags(Global::Active_person[index_vector].get_moneybags());
                        Global::save();
                    }
                }
                Global::save_vec_tran();
                this->close();
                Client *x=new Client(index_vector);
                x->setIndex_vector(index_vector);
                x->show();
            }
            else
            {
                ui->lineEdit_pssword->setStyleSheet("background: rgb(255,0,0);");
            }
        }
        else
        {
            if(ui->lineEdit_pssword->text().toInt()==pass)
            {
                Global::vec_tran.push_back(qMakePair(qMakePair(ui->lineEdit_price->text().toInt(),Global::Active_person[index_vector].get_user_name()),qMakePair("buy",now) ));
                for(int i=0;i<Global::Shopping_cart[index_vector].size();i++)
                {
                    if(Global::serch_id_cloths(Global::Shopping_cart[index_vector][i].first)!=-1)
                        Global::vec_tran.push_back(qMakePair(qMakePair(ui->lineEdit_price->text().toInt(), Global::vec_article_cloths[Global::serch_id_cloths(Global::Shopping_cart[index_vector][i].first)].get_seller_username()),qMakePair("sell",now) ));
                    else if(Global::serch_id_sporting_goods(Global::Shopping_cart[index_vector][i].first)!=-1)
                    {
                        Global::vec_tran.push_back(qMakePair(qMakePair(ui->lineEdit_price->text().toInt(), Global::vec_article_sporting_goods[Global::serch_id_sporting_goods(Global::Shopping_cart[index_vector][i].first)].get_seller_username()),qMakePair("sell",now) ));
                    }
                }
                Global::buy=1;
                for(int i=0;i<Global::vec_person.size();i++)
                {
                    if(Global::vec_person[i].get_user_name()==username)
                    {
                        Global::vec_person[i].setMoneybags(Global::vec_person[i].get_moneybags()+ui->lineEdit_price->text().toInt());
                        Global::save();
                    }
                }
                Global::save_vec_tran();
                this->close();
                Client *x=new Client(index_vector);
                x->setIndex_vector(index_vector);
                x->show();
            }
            else
            {
                ui->lineEdit_pssword->setStyleSheet("background: rgb(255,0,0);");

            }
        }
    }

}


void Transaction::on_pushButton_cancel_clicked()
{
    Client *x=new Client(index_vector);
    x->setIndex_vector(index_vector);
    x->show();
    this->close();
}

int Transaction::getIndex_vector() const
{
    return index_vector;
}

void Transaction::setIndex_vector(int newIndex_vector)
{
    index_vector = newIndex_vector;
}



void Transaction::on_checkBox_robot_stateChanged(int arg1)
{
    if(arg1==0)
    {
        ui->pushButton_password->hide();
        ui->lineEdit_pssword->hide();
    }
    else
    {
        ui->pushButton_password->show();
        ui->lineEdit_pssword->show();
    }
}

