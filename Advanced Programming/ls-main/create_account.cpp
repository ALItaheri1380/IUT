#include "create_account.h"
#include "ui_create_account.h"
#include "QMessageBox"
#include "QString"
#include "string"
#include "Person.h"
bool type{0};
Create_account::Create_account(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Create_account)
{
    ui->setupUi(this);
    this->setFixedSize(954,581);
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
}


Create_account::~Create_account()
{
    delete ui;
}

void Create_account::on_buttonBox_accepted()
{
    QString name, username, password, password2, phone, address, mail; int type;
    name=ui->lineEdit_name->text();
    username=ui->lineEdit_username->text();
    password=ui->lineEdit_password->text();
    password2=ui->lineEdit_repeatpassword->text();
    phone=ui->lineEdit_phone->text();
    address=ui->textEdit_address->toPlainText();
    mail=ui->lineEdit_Email->text();
    type=ui->radioButton_clinet->isChecked();
    if(type>0)
    {
        type =1;
    }
    else
        type=2;
    //bool t = 0;
    bool create_successfully=1;
    Global glob;

    for (int i = 0; i < glob.vec_person.size(); i++)
    {
        if (glob.vec_person[i].get_user_name() == username)
        {
            create_successfully=0;
            QMessageBox *qm=new QMessageBox(this);
            qm->setText("useranme is token");
            qm->exec();
        }
    }
    if (password != password2 &&create_successfully)
    {
        create_successfully=0;
        QMessageBox *qm=new QMessageBox(this);
        qm->setText("those password didn't match");
        qm->exec();
    }
    if (phone.size() != 11 && create_successfully)
    {
        create_successfully=0;
        QMessageBox *qm=new QMessageBox(this);
        qm->setText("phone number must be have 11 digits");
        qm->exec();
    }
    int t1=mail.toStdString().find(".com");
    int t2=mail.toStdString().find("@");
    if ((t1==-1 || t2==-1) && (create_successfully))
    {
        create_successfully=0;
        QMessageBox *qm=new QMessageBox(this);
        qm->setText("mail must be have @ , .com");
        qm->exec();
    }
    if(create_successfully)
    {
        Person x;
        x.set(name, username, phone, address, password, mail,0 ,type);
        glob.vec_person.push_back(x);
        glob.save();
    }
}

int Create_account::getIndex_vector() const
{
    return index_vector;
}

void Create_account::setIndex_vector(int newIndex_vector)
{
    index_vector = newIndex_vector;
}
