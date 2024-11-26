#include "thread.h"
#include "ui_thread.h"
#include "server_store.h"

thread::thread(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::thread)
{
    ui->setupUi(this);
}

thread::~thread()
{
    delete ui;
}

void thread::on_pushButton_clicked()
{
    server_store* temp = new server_store;
    temp->run();
}

