#include "markaz.h"
#include "ui_markaz.h"
#include"jadval.h"
#include<QDesktopServices>
#include <QUrl>
markaz::markaz(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::markaz)
{
    ui->setupUi(this);
}

markaz::~markaz()
{
    delete ui;
}

void markaz::on_pushButton_clicked()
{
    jadval* d = new jadval();
    d->show();
    close();
}


void markaz::on_pushButton_2_clicked()
{
    QString link = "https://maps.app.goo.gl/MJSLE5rifJgwv91r5";
    QDesktopServices::openUrl(QUrl(link));
}


void markaz::on_pushButton_3_clicked()
{
    QString link = "https://maps.app.goo.gl/aGuFUUdpAtnKWBEb6";
    QDesktopServices::openUrl(QUrl(link));
}


void markaz::on_pushButton_4_clicked()
{
    QString link = "https://maps.app.goo.gl/bpE8wUurZtDM2jFR9";
    QDesktopServices::openUrl(QUrl(link));
}

void markaz::on_pushButton_5_clicked()
{
    QString link = "https://maps.app.goo.gl/V8qRjkSHUkgM3HgK8";
    QDesktopServices::openUrl(QUrl(link));
}


void markaz::on_pushButton_6_clicked()
{
    QString link = "https://maps.app.goo.gl/CfFBFiuQmPaM77j79";
    QDesktopServices::openUrl(QUrl(link));
}
void markaz::on_pushButton_7_clicked()
{
    QString link = "https://maps.app.goo.gl/goSHck7Qt28cv1BG7";
    QDesktopServices::openUrl(QUrl(link));
}
void markaz::on_pushButton_8_clicked()
{
    QString link = "https://maps.app.goo.gl/UFmhLkohjJkey6Vm6";
    QDesktopServices::openUrl(QUrl(link));
}
void markaz::on_pushButton_9_clicked()
{
    QString link = "https://maps.app.goo.gl/JdigUXkHAoeXraD78";
    QDesktopServices::openUrl(QUrl(link));
}
void markaz::on_pushButton_10_clicked()
{
    QString link = "https://maps.app.goo.gl/5cZJMcWgRVXwUrLP8";
    QDesktopServices::openUrl(QUrl(link));
}
void markaz::on_pushButton_11_clicked()
{
    QString link = "https://maps.app.goo.gl/kNoDRWojWzg1qz3a9";
    QDesktopServices::openUrl(QUrl(link));
}


void markaz::on_pushButton_12_clicked()
{
    QString link = "https://maps.app.goo.gl/RnDPRXVcd4LwTgRB6";
    QDesktopServices::openUrl(QUrl(link));
}


void markaz::on_pushButton_13_clicked()
{
    QString link = "https://maps.app.goo.gl/2mh7EqjpXQSriWY66";
    QDesktopServices::openUrl(QUrl(link));
}

