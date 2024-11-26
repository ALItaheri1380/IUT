#include "add_kala.h"
#include "ui_add_kala.h"
#include "customer.h"
#include "QFile"
#include "qdir.h"
#include "QFileDialog"
#include "Global.h"
add_kala::add_kala(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::add_kala)
{
    ui->setupUi(this);
    this->setFixedSize(1241,688);
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    ui->comboBox_brand->hide();
    ui->comboBox_color->hide();
    ui->comboBoxgender_mat->hide();
    ui->comboBoxgender->hide();
    ui->lineEdit_weight->hide();
    ui->checkBox_gennder->hide();
    file=":/new/prefix1/null.png";
}

add_kala::~add_kala()
{
    delete ui;
}

void add_kala::on_pushButton_back_clicked()
{
    customer *x=new customer(index_vector);
    x->setIndex_vector(this->getIndex_vector());
    this->close();
    x->show();
}


void add_kala::on_pushButton_addphoto_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,"open",QDir::homePath());
    file=fileName;
    if (file=="")
        file=":/new/prefix1/null.png";
    QString x="QWidget {background-image: url("+file+") ;}";
    ui->widget_photo->setStyleSheet(x);
}


void add_kala::on_push_buttonconfirm_clicked()
{
    if(type==0)
    {
        type=0;
        name=ui->lineEdit_name->text();
        price=ui->spinBox_price->value();
        number=ui->spinBox_number->value();
        color=ui->comboBox_color->currentText();
        weight=ui->lineEdit_weight->text().toInt();
        brand=ui->comboBox_brand->currentText();
        gender=ui->comboBoxgender->currentText();
        cloths x(type , name , file , Global::Active_person[index_vector].get_user_name() , brand , color,weight,price,number,gender);
        Global::vec_article_cloths.push_back(x);
        customer::vec_cloths[index_vector].push_back(x);

    }
    else
    {
        type=1;
        name=ui->lineEdit_name->text();
        price=ui->spinBox_price->value();
        number=ui->spinBox_number->value();
        color=ui->comboBox_color->currentText();
        weight=ui->lineEdit_weight->text().toInt();
        brand=ui->comboBox_brand->currentText();
        gender=ui->comboBoxgender_mat->currentText();
        Sporting_goods x(type , name , file , Global::Active_person[index_vector].get_user_name() , brand , color,weight,price,number,gender);
        Global::vec_article_sporting_goods.push_back(x);
        customer::vec_sporting[index_vector].push_back(x);
    }
    Global::save_article();
    customer *x=new customer(index_vector);
    x->setSize_of_widget(x->getSize_of_widget()+1);
    x->setIndex_vector(this->getIndex_vector());
    x->show();
    this->close();

}


void add_kala::on_radioButton_Equipment_clicked()
{
    type=1;
    ui->checkBox_gennder->setText("material");
    ui->checkBox_gennder->show();
}


void add_kala::on_radioButton_cloths_clicked()
{
    type=0;
    ui->checkBox_gennder->setText("gender");
    ui->checkBox_gennder->show();
}


void add_kala::on_checkBox_color_stateChanged(int arg1)
{
    if(arg1)
    {
        ui->comboBox_color->show();
    }
    else
    {
        ui->comboBox_color->hide();
    }
}


void add_kala::on_checkBox_weight_stateChanged(int arg1)
{
    if(arg1)
    {
        ui->lineEdit_weight->show();
    }
    else
    {
        ui->lineEdit_weight->hide();
    }
}


void add_kala::on_checkBox_brand_stateChanged(int arg1)
{
    if(arg1)
    {
        ui->comboBox_brand->show();
    }
    else
    {
        ui->comboBox_brand->hide();
    }
}


void add_kala::on_checkBox_gennder_stateChanged(int arg1)
{
    if(arg1)
    {
        if(type==0)
            ui->comboBoxgender->show();
        else
            ui->comboBoxgender_mat->show();
    }
    else
    {
        ui->comboBoxgender->hide();
        ui->comboBoxgender_mat->hide();
    }
}

int add_kala::getIndex_vector() const
{
    return index_vector;
}

void add_kala::setIndex_vector(int newIndex_vector)
{
    index_vector = newIndex_vector;
}

