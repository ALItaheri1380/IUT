#include <QApplication>
#include "thread.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    thread w;
    w.show();
    return a.exec();
}
