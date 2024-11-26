#include "test.h"
#include "ui_test.h"
#include"widget_transactions.h"
#include"widget_show_kala_customer.h"
#include "QMessageBox"
#include "qicon.h"
test::test(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::test)
{
    widget_show_kala_customer *d=new widget_show_kala_customer[8];
    ui->setupUi(this);

    for(int i=0;i<7;i++)
    {
        QListWidgetItem *m_ulitems = new QListWidgetItem(QIcon(":/new/prefix1/BitcoinAd.gif"),"bokon bozorg");
        ui->listWidget->addItem(m_ulitems);
    }
}

test::~test()
{
    delete ui;
}

