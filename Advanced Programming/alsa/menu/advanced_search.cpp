#include "advanced_search.h"
#include "ui_advanced_search.h"

advanced_search::advanced_search(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::advanced_search)
{
    ui->setupUi(this);

    ui->lineEdit_8->setVisible(0);
    ui->lineEdit_9->setVisible(0);
    ui->label_8->setVisible(0);
    ui->label_9->setVisible(0);
}

advanced_search::~advanced_search()
{
    delete ui;
}

void advanced_search::on_comboBox_3_currentIndexChanged(int index)
{
    if(index)
    {
        ui->lineEdit_8->setVisible(1);
        ui->lineEdit_9->setVisible(1);
        ui->label_8->setVisible(1);
        ui->label_9->setVisible(1);

        if(index == 1)
        {
            ui->label_8->setText("رم");
            ui->label_9->setText("خافظه");
        }

        if(index == 2)
        {
            ui->label_8->setText("اندروید");
            ui->label_9->setText("خافظه");
        }

        if(index == 3)
        {
            ui->label_8->setText("سایز");
            ui->label_9->setText("نوع");
        }

        if(index == 4)
        {
            ui->label_8->setText("برند");
            ui->label_9->setText("نوع");
        }

        return;
    }

    ui->lineEdit_8->setVisible(0);
    ui->lineEdit_9->setVisible(0);
    ui->label_8->setVisible(0);
    ui->label_9->setVisible(0);
}

void advanced_search::on_buttonBox_accepted()
{
    QString cat = ui->comboBox_3->currentText()[0];
    QString color = ui->comboBox_2->currentText();
    QString sort;

    int x = ui->comboBox_4->currentIndex();

    if(x == 0)
        sort = "none";

    if(x == 1)
        sort = "sell";

    if(x == 2)
        sort = "seen";

    if(x == 3)
        sort = "dis";

    QString info1 = ui->lineEdit_8->text();
    QString info2 = ui->lineEdit_9->text();

    int state;

    if(ui->comboBox->currentText() == "موجود")
        state = 1;

    if(ui->comboBox->currentText() == "ناموجود")
        state = 0;

    if(ui->comboBox->currentText() == "All")
        state = 2;

    if(info1 == "")
    {
        info1 = "All";
    }

    if(info2 == "")
    {
        info2 = "All";
    }

    long long min = ui->lineEdit_2->text().toLongLong();
    long long max = ui->lineEdit_3->text().toLongLong();

    if(max == 0)
    {
        max = 1000000000;
    }

    emit send_data(cat,color,sort,state,min,max,info1,info2);
}
