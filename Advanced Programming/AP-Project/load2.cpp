#include "load2.h"
#include "ui_load2.h"

load2::load2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::load2)
{
    ui->setupUi(this);
}

load2::~load2()
{
    delete ui;
}
