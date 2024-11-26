#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pushButton->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_MainWindow_iconSizeChanged(const QSize &iconSize)
{
    //ui->lineEdit->hide();
}

void MainWindow::on_checkBox_stateChanged()
{
    //x1 x2;
}


void MainWindow::on_comboBox_currentIndexChanged(const QString &arg1)
{
    ui->pushButton->setText(arg1);
    ui->pushButton->show();
}
