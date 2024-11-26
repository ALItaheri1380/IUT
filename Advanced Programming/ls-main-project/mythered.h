#ifndef MYTHERED_H
#define MYTHERED_H


#include <QThread>
#include "Person.h"
class mythered : public QThread
{
public:
    mythered();
    void run();
    void set(int t , Person t1);
    static int getCount();
    static void setCount(int newCount);
    static int count;
private:
    int type;
    Person ac;
};

#endif // MYTHERED_H
