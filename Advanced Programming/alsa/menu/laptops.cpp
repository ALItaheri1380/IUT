#include "laptops.h"
#include "ui_laptops.h"
#include <QMessageBox>

laptops::laptops(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::laptops)
{
    ui->setupUi(this);
    setWindowTitle("افزودن لپ تاپ");
    ui->lineEdit_2->setValidator( new QIntValidator(0, 999999999, this) );
    ui->lineEdit_3->setValidator( new QIntValidator(0, 200000, this) );
}

laptops::~laptops()
{
    delete ui;
}

void laptops::on_pushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "لطفا تصویر محصول مورد نظر را انتخاب کنید", "/", tr("Image Files (*.png *.jpg *.bmp)"));

    if (fileName.isEmpty())
        return;

    imagePixmap.load(fileName);
    ui->label->setPixmap(imagePixmap);
}

void laptops::getUserName(QString str)
{
    username = str;
}

void laptops::on_pushButton_3_clicked()
{
    QString filename= "prudoct.txt";

    QDir dir;
    dir.mkdir(QString(".\\prudoct_picture"));
    imagePixmap.save(QString(".\\prudoct_picture\\") + QString::number(photo_name()) + ".png");

    QFile file(filename);
    file.open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Append);
    QTextStream stream( &file );

    laptops temp;

    temp.name = ui->lineEdit->text();
    temp.price = ui->lineEdit_2->text();
    temp.count = ui->spinBox->value();
    temp.coloer = ui->comboBox->currentText();
    temp.space = ui->lineEdit_3->text().toInt();
    temp.ram = ui->spinBox_2->value();
    temp.otherDetail = ui->plainTextEdit->toPlainText();

    if(temp.name == "" || temp.price == "")
    {
        QMessageBox::warning(this,"اخطار","نام و قیمت محصول نمی تواند خالی باشد!");
        return;
    }

    stream << username << "," << temp.name << "," << temp.price << "," << temp.count << ","
           << temp.coloer << ",0,1,0," << temp.ram << "," << temp.space << "," << temp.otherDetail << ","
           << QString::number(photo_name()-1) << ",l\n";

    file.close();
    close();
}

void laptops::on_pushButton_2_clicked()
{
    close();
}
