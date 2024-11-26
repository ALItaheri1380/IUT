#include "persongclientt.h"
#include<QFile>
#include<QTextStream>
personGclientt::personGclientt()
{

}
void personGclientt::read_file(QString filename){
    QFile myfile(filename);
    if(!myfile.open(QFile::ReadOnly |QFile::Text))
    {
       return;
    }
     QTextStream in(&myfile);
     while (!in.atEnd())
     {
            QString myText = in.readLine();
            QStringList List = myText.split(',');
                Name.push_back(List[0]);
                Password.push_back(List[1]);
                Address_vect.push_back(List[2]);
                PhoneNumber.push_back(List[3]);
                Card_number.push_back(List[4]);
                cvv2.push_back(List[5]);
                Money.push_back(List[6]);

       }
         myfile.close();
}
void personGclientt::write_to_file(QString filename){
    QFile file(filename);
    if(!file.open(QFile::WriteOnly | QFile::Text))
    {
      return;
    }
    QTextStream out(&file);
    int i=0;
    while (i < Name.size())
    {
        out <<Name[i]<<','
              <<Password[i]<<','
              <<Address_vect[i]<<','
              <<PhoneNumber[i]<<','
              <<Card_number[i]<<','
              <<cvv2[i]<<','
              <<Money[i]<<'\n';
        i++;
    }
    file.flush();
    file.close();
}
