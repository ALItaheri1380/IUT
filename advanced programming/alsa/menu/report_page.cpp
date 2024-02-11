#include "report_page.h"
#include "ui_report_page.h"
#include <QFile>
#include <QMessageBox>

report_page::report_page(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::report_page)
{
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
}

report_page::~report_page()
{
    delete ui;
}

void report_page::getId(QString usern,QString id)
{
    ui->setupUi(this);

    username = usern;
    this->id = id;
}

void report_page::on_buttonBox_accepted()
{
    QString filename= "report.txt";

    QFile file(filename);
    file.open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Append);
    QTextStream stream( &file );

    QString uname = username;
    QString pid = id;
    QString type = (ui->radioButton->isChecked()) ? "c" : "p";
    QString detail = ui->plainTextEdit->toPlainText();

    stream << uname << "," << pid << "," << type << ",-," << detail << "\n";
    file.close();

    QMessageBox::information(this,"تایید","گزارش شما ثبت شد!");
}

