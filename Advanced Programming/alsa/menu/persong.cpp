#include "persong.h"
#include<QFile>
#include <QDialog>
#include<QTextStream>
personG::personG()
{

}

void personG::Read_file(){
    QFile myfile("Login_customer.txt");
    if(!myfile.open(QFile::ReadOnly |QFile::Text))
    {
       return;
    }
     QTextStream  in(&myfile);
     while (!in.atEnd())
     {
            QString myText = in.readLine();
            QStringList List = myText.split(',');
             name.push_back(List[0]);
             password.push_back(List[1]);
             card_number.push_back(List[2]);
             CVV2.push_back(List[3]);
             money.push_back(List[4]);
             Block.push_back(List[5]);
       }
         myfile.close();
}
void personG::Write_to_file(){
    QFile file("Login_customer.txt");
    if(!file.open(QFile::WriteOnly | QFile::Text))
    {
      return;
    }
    QTextStream out(&file);
    int i=0;
    while (i < name.size())
    {
        out <<name[i]<<','
             <<password[i]<<','
             <<card_number[i]<<','
             <<CVV2[i]<<','
             <<money[i]<<','
             <<Block[i]<<"\n";
        i++;
    }
    file.flush();
    file.close();
}
