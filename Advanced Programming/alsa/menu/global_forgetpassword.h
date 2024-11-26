#ifndef GLOBAL_FORGETPASSWORD_H
#define GLOBAL_FORGETPASSWORD_H


class global_forgetPassword
{
public:

          global_forgetPassword();

protected:

           virtual void on_buttonBox_accepted()   =  0;

             void chekVal(bool);

              bool isvalid;

};

#endif // GLOBAL_FORGETPASSWORD_H
