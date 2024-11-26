#ifndef PERSONGCLIENTT_H
#define PERSONGCLIENTT_H
#include<qvector.h>

class personGclientt
{
public:
    personGclientt();
protected:
    void  write_to_file(QString filename);
    void  read_file(QString filename);
    QVector<QString> Address_vect;
    QVector<QString> PhoneNumber;
    QVector<QString > Name;
    QVector<QString > Password;
    QVector<QString > Card_number;
    QVector<QString > cvv2;
    QVector<QString > Money;
};

#endif // PERSONGCLIENTT_H
