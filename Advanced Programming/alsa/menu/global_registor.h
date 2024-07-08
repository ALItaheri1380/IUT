#ifndef GLOBAL_REGISTOR_H
#define GLOBAL_REGISTOR_H
#include<QString>
class global_registor
{
public:

    global_registor();

protected:

         virtual void on_buttonBox_accepted() = 0;

         virtual void final_regist() = 0;

         QString money_;

};

#endif // GLOBAL_REGISTOR_H
