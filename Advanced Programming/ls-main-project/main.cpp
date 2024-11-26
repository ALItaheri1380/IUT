#include <QApplication>
#include "Global.h"
#include "login.h"
#include "load1.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Global::load();
    Global::load_article();
    Global::load_buyer();
    Global::load_tran();
    load1 *x=new load1;
    x->show();
    return a.exec();
}
