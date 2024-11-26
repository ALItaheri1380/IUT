#ifndef PERSONG_H
#define PERSONG_H
#include <QVector>

class personG
{
public:
        personG();
protected:
    QVector<QString > name;
    QVector<QString > password;
    QVector<QString > card_number;
    QVector<QString > CVV2;
    QVector<QString > money;
    QVector<QString > Block;
    void Read_file();
    void Write_to_file();
};

#endif // PERSONG_H
