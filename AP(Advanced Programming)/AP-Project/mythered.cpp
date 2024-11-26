#include "mythered.h"
#include"Global.h"
#include "login.h"
#include "admin.h"
#include "customer.h"
#include "client.h"
#include "game.h"
int mythered::count=0;
mythered::mythered()
{

}
void mythered::run()
{

    if (type==0)
    {
        Global::Active_person[count]=ac;
        Admin *x= new Admin(count);
        x->setIndex_vector(count);
            count++;
        x->show();
      //  this->close();
    }
    else if(type==1)
    {
        Global::Active_person[count]=ac;
        MainWindow *x=new MainWindow;
        x->setIndex_vector(count);
            count++;
        x->show();
    }
    else
    {
        Global::Active_person[count]=ac;
        customer *x= new customer(count);
        x->setIndex_vector(count);
            count++;
        x->show();
       // this->close();
    }

}

void mythered::set(int t, Person t1)
{
    type=t;
    ac=t1;
}

int mythered::getCount()
{
    return count;
}

void mythered::setCount(int newCount)
{
    count = newCount;
}
