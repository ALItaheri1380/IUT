#include "jadval.h"
#include "./ui_jadval.h"
#include"markaz.h"
#include<QUrl>
#include<QDesktopServices>
jadval::jadval(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::jadval)
{
    ui->setupUi(this);
}

jadval::~jadval()
{
    delete ui;
}
void jadval::on_pushButton_clicked()
{
      markaz* d = new markaz();
      d->show();
      close();
}


void jadval::on_pushButton_2_clicked()
{
    close();
}


void jadval::on_pushButton_3_clicked()
{
    QString link = "https://maps.app.goo.gl/421585J12DB4ccqL7";
    QDesktopServices::openUrl(QUrl(link));
}


void jadval::on_pushButton_4_clicked()
{
    QString link = "https://maps.app.goo.gl/LhcARj6iYmj9TE3z8";
    QDesktopServices::openUrl(QUrl(link));
}


void jadval::on_pushButton_5_clicked()
{
    QString link = "https://maps.app.goo.gl/TU8UKrKEiHgWSipj9";
    QDesktopServices::openUrl(QUrl(link));
}


void jadval::on_pushButton_6_clicked()
{
    QString link = "https://maps.app.goo.gl/UJ8voN5iRAyp4k9w5";
    QDesktopServices::openUrl(QUrl(link));
}


void jadval::on_pushButton_7_clicked()
{
    QString link = "https://maps.app.goo.gl/kU8mhjQSvczyfJHW7";
    QDesktopServices::openUrl(QUrl(link));
}


void jadval::on_pushButton_8_clicked()
{
    QString link = "https://maps.app.goo.gl/m9FVQMM94Kouk2AGA";
    QDesktopServices::openUrl(QUrl(link));
}


void jadval::on_pushButton_9_clicked()
{
    QString link = "https://maps.app.goo.gl/5nenrXkeDjbdW9b97";
    QDesktopServices::openUrl(QUrl(link));
}


void jadval::on_pushButton_10_clicked()
{
    QString link = "https://maps.app.goo.gl/a5aQQkJ7cPhaWxws8";
    QDesktopServices::openUrl(QUrl(link));
}


void jadval::on_pushButton_11_clicked()
{
    QString link = "https://maps.app.goo.gl/6C6wQUnoN3gm4NpP8";
    QDesktopServices::openUrl(QUrl(link));
}


void jadval::on_pushButton_12_clicked()
{
    QString link = "https://maps.app.goo.gl/5SgmipRBvEinwPKP8";
    QDesktopServices::openUrl(QUrl(link));
}


void jadval::on_pushButton_13_clicked()
{
    QString link = "https://maps.app.goo.gl/ecKnHsycnKFg7Qup7";
    QDesktopServices::openUrl(QUrl(link));
}


void jadval::on_pushButton_14_clicked()
{
    QString link = "https://maps.app.goo.gl/AW1oUbkh4tjXVaHN7";
    QDesktopServices::openUrl(QUrl(link));
}

void jadval::on_pushButton_15_clicked()
{
    QString link = "https://maps.app.goo.gl/SRxc7UTnkyvyb1PW8";
    QDesktopServices::openUrl(QUrl(link));
}


void jadval::on_pushButton_16_clicked()
{
    QString link = "https://maps.app.goo.gl/CfFBFiuQmPaM77j79";
    QDesktopServices::openUrl(QUrl(link));
}


void jadval::on_pushButton_17_clicked()
{
    QString link = "https://maps.app.goo.gl/2tuDmNpbAhwfc8tA6";
    QDesktopServices::openUrl(QUrl(link));
}


void jadval::on_pushButton_18_clicked()
{
    QString link = "https://maps.app.goo.gl/ZBmb8fX2Kz11HN9z9";
    QDesktopServices::openUrl(QUrl(link));
}


void jadval::on_pushButton_19_clicked()
{
    QString link = "https://maps.app.goo.gl/ahU5C1yY7vvp2VVc7";
    QDesktopServices::openUrl(QUrl(link));
}


void jadval::on_pushButton_20_clicked()
{
    QString link = "https://maps.app.goo.gl/XmGpfbbahEgtvtoN8";
    QDesktopServices::openUrl(QUrl(link));
}


void jadval::on_pushButton_21_clicked()
{
    QString link = "https://maps.app.goo.gl/Uo6nUYxLznyQv59UA";
    QDesktopServices::openUrl(QUrl(link));
}
void jadval::on_pushButton_22_clicked()
{
    QString link = "https://maps.app.goo.gl/oeEphjVV8Twphn3k9";
    QDesktopServices::openUrl(QUrl(link));
}


