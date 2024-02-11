#include "edit_product.h"
#include "ui_edit_product.h"
#include <QFile>
#include <QDir>
#include <QMessageBox>
#include <QFileDialog>

Edit_product::Edit_product(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Edit_product)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    setWindowTitle("ویرایش محصول");
}

Edit_product::~Edit_product()
{
    delete ui;
}

void Edit_product::getPruductId(QString str)
{
    QFile inputFile("prudoct.txt");
    QStringList split;

    id = str;

    if (inputFile.open(QIODevice::ReadOnly))
    {
       QTextStream in(&inputFile);

       for (int i = 0; !in.atEnd() ; i++)
       {
          QString line = in.readLine();
          split = line.split(",");

          if(split[11] == str)
             break;
       }

       inputFile.close();
    }

    QString cat;

    if(split[12] == "l")
    {
        cat = "لپ تاپ";
        ui->label_11->setText("رم");
        ui->label_6->setText("خافظه");
    }

    if(split[12] == "w")
    {
        cat = "ساعت مچی";
        ui->label_11->setText("برند");
        ui->label_6->setText("نوع");
    }

    if(split[12] == "c")
    {
        cat = "پوشاک";
        ui->label_11->setText("سایز");
        ui->label_6->setText("نوع");
    }

    if(split[12] == "p")
    {
        cat = "موبایل";
        ui->label_11->setText("اندروید");
        ui->label_6->setText("خافظه");
    }

    QPixmap photo_source{".\\prudoct_picture\\" + str + ".png"};
    ui->label->setPixmap(photo_source.scaled(200,200));

    ui->lineEdit->setText(split[1]);
    ui->lineEdit_2->setText(split[2]);
    ui->lineEdit_3->setText(split[5]);
    ui->lineEdit_6->setText(split[3]);
    ui->lineEdit_7->setText(cat);
    ui->comboBox->setEditText(split[4]);
    ui->lineEdit_9->setText(split[8]);
    ui->lineEdit_5->setText(split[9]);
    ui->plainTextEdit->setPlainText(split[10]);
}

void Edit_product::on_pushButton_clicked()
{
    close();
}

void Edit_product::on_pushButton_2_clicked()
{
    QString filename = "prudoct.txt";
    QDir dir(".\\prudoct_picture");
    imagePixmap.save(QString(".\\prudoct_picture\\") + id + ".png");

    if(ui->lineEdit->text() == "" || ui->lineEdit_2->text() == "")
    {
        QMessageBox::warning(this,"اخطار","نام و قیمت محصول نمی تواند خالی باشد!");
        return;
    }

    QVector<QString> lines;
    QFile inputFile("prudoct.txt");
    QStringList split;
    QString line;

    if (inputFile.open(QIODevice::ReadOnly))
    {
       QTextStream in(&inputFile);

       for (int i = 0; ; i++)
       {
          line = in.readLine();
          split = line.split(",");

          if(line == "")
              break;

          if(split[11] == id)
          {
              line = split[0] + "," + ui->lineEdit->text() + "," + ui->lineEdit_2->text() + "," + ui->lineEdit_6->text() + "," +
              ui->comboBox->currentText() + "," + ui->lineEdit_3->text() + "," + split[6] + "," + split[7] + "," +
              ui->lineEdit_9->text() + "," + ui->lineEdit_5->text() + "," + ui->plainTextEdit->toPlainText() + "," +
              split[11] + "," + split[12];
          }

          lines.push_back(line);
       }

       inputFile.close();
    }

    QFile file("prudoct.txt");
    file.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text);
    QTextStream stream( &file );

    for(int i = 0; i < lines.length(); i++)
        stream << lines.at(i) << "\n";

    file.close();
    lines.clear();

    QMessageBox::information(this,"تایید","ویرایش محصول با موفقیت انجام شد");
    close();
    emit show_end("end");
}

void Edit_product::on_pushButton_3_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "لطفا تصویر محصول مورد نظر را انتخاب کنید", "/", tr("Image Files (*.png *.jpg *.bmp)"));

    if (fileName.isEmpty())
        return;

    imagePixmap.load(fileName);
    ui->label->setPixmap(imagePixmap.scaled(200,200));
}
