#include "edituser.h"
#include "ui_edituser.h"
#include "Global.h"
#include "qmessagebox.h"
#include "admin.h"
EditUser::EditUser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditUser)
{
    ui->setupUi(this);
    this->setFixedSize(521,331);
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
}

EditUser::~EditUser()
{
    delete ui;
}

void EditUser::set(int ind)
{
    this->ind=ind;
    Person x=Global::vec_person[ind];
    ui->lineEdit_Name->setText(x.get_name());
    ui->lineEdit_UesrName->setText(x.get_user_name());
    ui->lineEdit_Address->setText(x.get_address());
    ui->lineEdit_Phon->setText(x.get_phone_number());
    ui->lineEdit_Email->setText(x.get_Mail());
}


void EditUser::on_pushButton_Save_clicked()
{
    QString name=ui->lineEdit_Name->text();
    QString user=ui->lineEdit_UesrName->text();
    QString mail=ui->lineEdit_Email->text();
    QString address=ui->lineEdit_Address->text();
    QString phone=ui->lineEdit_Phon->text();
    Global::vec_person[ind].set(name , user , phone , address , Global::vec_person[ind].get_password() ,mail,Global::vec_person[ind].get_ban(),Global::vec_person[ind].get_type(),Global::vec_person[ind].get_moneybags());
    Global::save();
    this->close();
}


void EditUser::on_pushButton_Delete_clicked()
{
    Global::vec_person.remove(ind);
    Global::save();
    this->close();

}


void EditUser::on_pushButton_Ban_clicked()
{
    bool o=Global::vec_person[ind].get_ban();
    if(o)
    {
        QMessageBox *x=new QMessageBox;
        x->setText("unbaned");
        x->exec();
        Global::vec_person[ind].setBan(0);
    }
    else
    {
        QMessageBox *x=new QMessageBox;
        x->setText("baned");
        x->exec();
        Global::vec_person[ind].setBan(1);
    }
    Global::save();
    this->close();
}


void EditUser::on_pushButton_Cancel_clicked()
{
    this->close();
}

int EditUser::getIndex_vector() const
{
    return index_vector;
}

void EditUser::setIndex_vector(int newIndex_vector)
{
    index_vector = newIndex_vector;
}

