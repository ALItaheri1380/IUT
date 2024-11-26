#include "forget_password.h"
#include "ui_forget_password.h"
#include "Global.h"
#include "QMessageBox"
forget_password::forget_password(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::forget_password)
{
    ui->setupUi(this);
    this->setFixedSize(954,581);
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
}

forget_password::~forget_password()
{
    delete ui;
}

void forget_password::on_buttonBox_accepted()
{
    QString username, password, password2;
    username=ui->lineEdit_username->text();
    password=ui->lineEdit_new_password->text();
    password2=ui->lineEdit_repeat_password->text();
    Global glob;
    if (password != password2)
    {
        ui->lineEdit_repeat_password->setStyleSheet("background: rgb(255,0,0);");
    }
    else
    {
        bool username_valid=0;
        for (int i = 0; i < glob.vec_person.size(); i++)
        {
            if (username == glob.vec_person[i].get_user_name())
            {
                username_valid=1;
                glob.vec_person[i].set_password(password);
                glob.save();
            }
        }
        if (username_valid==0)
        {
            QMessageBox* qm=new QMessageBox(this);
            qm->setText("username doesn't exits");
            qm->exec();
        }
    }

}

int forget_password::getIndex_vector() const
{
    return index_vector;
}

void forget_password::setIndex_vector(int newIndex_vector)
{
    index_vector = newIndex_vector;
}
