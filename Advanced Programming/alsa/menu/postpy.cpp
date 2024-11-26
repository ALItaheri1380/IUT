#include "postpy.h"
#include "ui_postpy.h"
#include "getloc_by_py.h"
#include "increase_money.h"
#include <QMessageBox>
#include "jadval.h"

PostPy::PostPy(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PostPy)
{
    ui->setupUi(this);
}

PostPy::~PostPy()
{
    delete ui;
}

void PostPy::on_pushButton_2_clicked()
{
    getLoc_by_py* d = new getLoc_by_py(this);
    d->show();
    close();
}


void PostPy::on_pushButton_clicked()
{
    jadval* temp = new jadval{this};
    temp->show();
    close();
}

