#include "increase_money.h"
#include "ui_increase_money.h"
#include <qpixmap.h>
#include <QMessageBox>
#include <QFile>
increase_money::increase_money(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::increase_money)
{
    ui->setupUi(this);
}
increase_money::~increase_money()
{
    delete ui;
}
void increase_money::Read_file_prd(){
    QFile myfile("prudoct.txt");
    if(!myfile.open(QFile::ReadOnly |QFile::Text))
    {
       return;
    }
    QTextStream in(&myfile);
    while (!in.atEnd()){
            QString myText = in.readLine();
            QStringList List = myText.split(',');
            n_cl.push_back(List[0]);
            n_pr.push_back(List[1]);
            n_price.push_back(List[2]);
            n_num.push_back(List[3]);
            n_col.push_back(List[4]);
            n_dis.push_back(List[5]);
            n_seen.push_back(List[6]);
            n_num_buy.push_back(List[7]);
            n_glob1.push_back(List[8]);
            n_glob2.push_back(List[9]);
            n_exp.push_back(List[10]);
            n_id.push_back(List[11]);
            n_w.push_back(List[12]);
         }
         myfile.close();
}
void increase_money::Write_to_file_prd(){
    QFile file("prudoct.txt");
    if(!file.open(QFile::WriteOnly | QFile::Text))
    {
      qDebug() << " Could not open file for writing";
      return;
    }
    QTextStream out(&file);
    int i=0;
    while (i <n_cl.size())
    {
        out  <<n_cl[i]<<','
               << n_pr[i]<<','
               <<n_price[i]<<','
               <<n_num[i]<<','
               <<n_col[i]<<','
               << n_dis[i]<<','
               <<n_seen[i]<<','
               <<n_num_buy[i]<<','
               <<n_glob1[i]<<','
               <<n_glob2[i]<<','
               <<n_exp[i]<<','
               <<n_id[i]<<','
               <<n_w[i]<<'\n';
        i++;
    }
    file.flush();
    file.close();
}
/**************************************/
void increase_money::Read_file_buylist(){
    QFile myfile("buylist.txt");
    if(!myfile.open(QFile::ReadOnly |QFile::Text))
    {
       qDebug() << " Could not open the file for reading";
       return;
    }
    QTextStream in(&myfile);
    while (!in.atEnd()){
            QString myText = in.readLine();
            QStringList List = myText.split(',');
            customer_name.push_back(List[0]);
            client_name.push_back(List[1]);
            price.push_back(List[2]);
            counter.push_back(List[3]);
            id.push_back(List[4]);
         }
         myfile.close();
}

void increase_money:: Read_file_history(){
    QFile myfile("history.txt");
    if(!myfile.open(QFile::ReadOnly |QFile::Text))
    {
       qDebug() << " Could not open the file for reading";
       return;
    }
    QTextStream in(&myfile);
    while (!in.atEnd()){
            QString myText = in.readLine();
            QStringList List = myText.split(',');
            customer_name_his.push_back(List[0]);
            client_name_his.push_back(List[1]);
            price_his.push_back(List[2]);
            counter_his.push_back(List[3]);
         }
         myfile.close();
}
void increase_money::Write_to_file_history(){
    QFile file("history.txt");
    if(!file.open(QFile::WriteOnly | QFile::Text))
    {
      qDebug() << " Could not open file for writing";
      return;
    }
    QTextStream out(&file);
    int i=0;
    while (i <customer_name_his.size())
    {
        out << customer_name_his[i]<<','
        <<client_name_his[i]<<','
        <<price_his[i]<<','
        <<counter_his[i]
        <<Qt::endl;
        i++;
    }
    file.flush();
    file.close();
}
void increase_money::Write_to_file_remove(){
    QFile file("buylist.txt");
    if(!file.open(QFile::WriteOnly | QFile::Text))
    {
      qDebug() << " Could not open file for writing";
      return;
    }
    QTextStream out(&file);
    int i=0;
    while (i < customer_name_remove.size())
    {
        out << customer_name_remove[i]<<','
        <<client_name_remove[i]<<','
        <<price_remove[i]<<','
        <<counter_remove[i]<<','
        <<id_remove[i]
        <<Qt::endl;
        i++;
    }
    file.flush();
    file.close();
}
void increase_money::add_money(QString money)
{
    ui->lineEdit_4->setText(money);
}
void increase_money::increas()
{

    Read_file_prd();
    read_file("Login_client.txt");
    bool is_valid = false;
    int i = 0;
    for(i ; i < Name.size() ; i++){
        if(Card_number[i] == ui->lineEdit->text()){
            is_valid = true;
            break;
        }

    }
    if(!is_valid)
    {
        int ret;
        QMessageBox msgBox;
        msgBox.setText("این شماره کارت وجود ندارد!!!!");
        ret = msgBox.exec();
        return;
    }
    if(ui->lineEdit_2->text() == cvv2[i]&&
             ui->lineEdit_3->text() == Password[i])
        {
             check_buy = true;
             int M = Money[i].toInt();
             M = M - ui->lineEdit_4->text().toInt();
             if(M < 0){
                 int ret;
                 QMessageBox msgBox;
                 msgBox.setText("موجودی کافی نیست :(((((((");
                 ret = msgBox.exec();
                 increas_money_of_customer();
                 return;
             }

             Money.replace(i,QVariant(M).toString());
             write_to_file("Login_client.txt");
             int ret;
             QMessageBox msgBox;
             msgBox.setText("خرید با موفقیت انجام شد :)))))");
             ret = msgBox.exec();
             increas_money_of_customer();
             return;
        }
    else{
        int ret;
        QMessageBox msgBox;
        msgBox.setText("رمز یا سی وی وی 2 اشتباه است !!!! ");
        ret = msgBox.exec();
        return;
    }
}
void increase_money::add_item(QString money,QString user){
    ui->lineEdit_4->setText(money);
    username = user;
}
void increase_money::increas_money_of_customer()
{
    if(check_buy){
         Read_file_buylist();
         Read_file_history();
         Read_file();

         for(int i = 0 ; i < customer_name.size() ; i++)
         {
             if(client_name[i] == username){
                 customer_name_his.push_back(customer_name[i]);
                 client_name_his.push_back(client_name[i]);
                 price_his.push_back(price[i]);
                 counter_his.push_back(counter[i]);
                 for(int j = 0 ; j <name.size() ; j++ ){
                 if(customer_name[i] == name[j]){
                     int M = money[j].toInt() + price[i].toInt();
                     money.replace(j,QVariant(M).toString());
                   }
                 }
                 for (int k = 0 ; k < n_cl.size() ; k++){
                     if(n_id[k] ==id[i]){
                         int M = n_num[k].toInt() - counter[i].toInt();
                         QString tmp = QString::number(M);
                         n_num.replace(k,tmp);
                         Write_to_file_prd();
                     }
                 }
             }else{
                 customer_name_remove.push_back(customer_name[i]);
                 client_name_remove.push_back(client_name[i]);
                 price_remove.push_back(price[i]);
                 counter_remove.push_back(counter[i]);
                 id_remove.push_back(id[i]);
             }
         }
         Write_to_file();
         Write_to_file_history();
         Write_to_file_remove();
    }
}
void increase_money::on_buttonBox_accepted()
{
      increas();
}
