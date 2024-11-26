#include "clothing.h"
#include "ui_clothing.h"
#include <QMessageBox>

clothing::clothing(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::clothing)
{
    ui->setupUi(this);
    setWindowTitle("افزودن پوشاک");
}

clothing::~clothing()
{
    delete ui;
}

void clothing::on_pushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "لطفا تصویر محصول مورد نظر را انتخاب کنید", "/", tr("Image Files (*.png *.jpg *.bmp)"));

    if (fileName.isEmpty())
        return;

    imagePixmap.load(fileName);
    ui->label->setPixmap(imagePixmap);
}

void clothing::getUserName(QString str)
{
    username = str;
}

void clothing::on_pushButton_3_clicked()
{
    QString filename= "prudoct.txt";

    QDir dir;
    dir.mkdir(QString(".\\prudoct_picture"));
    imagePixmap.save(QString(".\\prudoct_picture\\") + QString::number(photo_name()) + ".png");

    QFile file(filename);
    file.open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Append);
    QTextStream stream( &file );

    clothing temp;

    temp.name = ui->lineEdit->text();
    temp.price = ui->lineEdit_2->text();
    temp.count = ui->spinBox->value();
    temp.coloer = ui->comboBox->currentText();
    temp.size = ui->comboBox_2->currentText();
    temp.type = ui->lineEdit_3->text();
    temp.otherDetail = ui->plainTextEdit->toPlainText();

    if(temp.name == "" || temp.price == "")
    {
        QMessageBox::warning(this,"اخطار","نام و قیمت محصول نمی تواند خالی باشد!");
        return;
    }

    stream << username << "," << temp.name << "," << temp.price << "," << temp.count << ","
           << temp.coloer << ",0,1,0," << temp.size << "," << temp.type << "," << temp.otherDetail << ","
           << QString::number(photo_name()-1) << ",c\n";

    file.close();
    close();
}

void clothing::on_pushButton_2_clicked()
{
    close();
}
