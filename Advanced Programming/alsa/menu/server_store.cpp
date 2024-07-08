#include "server_store.h"
#include "mainwindow.h"

server_store::server_store()
{

}
void server_store::run()
{
    MainWindow* temp = new MainWindow;
    temp->show();
}
