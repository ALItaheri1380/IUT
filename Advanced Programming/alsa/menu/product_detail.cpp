#include "product_detail.h"
#include "ui_product_detail.h"
#include <QFile>
#include <QMessageBox>
#include <QProcess>

Product_detail::Product_detail(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Product_detail)
{
    ui->setupUi(this);
    setWindowTitle("جزئیات محصول");
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
}

Product_detail::~Product_detail()
{
    delete ui;
}

void Product_detail::on_pushButton_clicked()
{
    close();
}

void Product_detail::getPruductId(QString str)
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
    ui->label->setPixmap(photo_source.scaled(240,240));

    ui->lineEdit->setText(split[1]);
    ui->lineEdit_2->setText(split[2]);
    ui->lineEdit_3->setText(split[5]);
    ui->lineEdit_4->setText(QString::number((split[2].toLongLong() * (100 - split[5].toInt())) / 100));
    ui->lineEdit_6->setText(split[3]);
    ui->lineEdit_7->setText(cat);
    ui->lineEdit_8->setText(split[4]);
    ui->lineEdit_9->setText(split[8]);
    ui->lineEdit_5->setText(split[9]);

    ui->plainTextEdit->setPlainText(split[10]);
}

void Product_detail::on_pushButton_2_clicked()
{
    QFile file("C:/Users/digitall home/Documents/Ap/alsa/python files/sound.txt");

    if(!file.open(QFile::WriteOnly | QFile::Text))
    {
      return;
    }

    QTextStream out(&file);
    out << id;
    file.flush();
    file.close();

    /***********************/

    QString path = "C:/Users/digitall home/Documents/Ap/alsa/python files";
    QString  command("python");
    QStringList params = QStringList() << "sound.py";
    QProcess *process = new QProcess();
    process->startDetached(command, params, path);
    process->waitForFinished();
    process->close();
}

