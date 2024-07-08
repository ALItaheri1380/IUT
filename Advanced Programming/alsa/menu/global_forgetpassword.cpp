#include "global_forgetpassword.h"
#include <QMessageBox>
global_forgetPassword::global_forgetPassword()
{
      isvalid = false;
}
void global_forgetPassword::chekVal(bool v)
{
    if(!v){
        int ret;
        QMessageBox msgBox;
        msgBox.setText("این کاربر وجود ندارد !!!!!");
        ret = msgBox.exec();
    }
}
