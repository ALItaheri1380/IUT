#include "getloc_by_py.h"
#include "ui_getloc_by_py.h"
#include<QProcess>
#include <QFile>
getLoc_by_py::getLoc_by_py(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::getLoc_by_py)
{
    ui->setupUi(this);
}
void getLoc_by_py::Write_to_file(){
    QFile file("C:/Users/digitall home/Documents/Ap/alsa/python files/PostPy.txt");
    if(!file.open(QFile::WriteOnly | QFile::Text))
    {
      qDebug() << " Could not open file for writing";
      return;
    }
    QTextStream out(&file);
    out <<ui->lineEdit->text()<<'\n'<<ui->lineEdit_2->text();
    file.flush();
    file.close();
}
getLoc_by_py::~getLoc_by_py()
{
    delete ui;
}

void getLoc_by_py::on_buttonBox_accepted()
{
     Write_to_file();
     QString path = "C:/Users/digitall home/Documents/Ap/alsa/python files";
     QString  command("python");
      QStringList params = QStringList() << "ali.py";
      QProcess *process = new QProcess();
      process->startDetached(command, params, path);
      process->waitForFinished();
      process->close();
}

