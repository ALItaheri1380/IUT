#include "product.h"
#include <QFile>
#include <QTextStream>

product::product()
{

}

int product::countlines(QString fname)
{
    QFile file(fname);
    int line_count = 0;

    QString line[10000];
    QTextStream in(&file);

    file.open(QIODevice::ReadWrite);

    while( !in.atEnd())
    {
        line[line_count]=in.readLine();
        line_count++;
    }

    file.close();
    return line_count;
}

int product::photo_name()
{
    QDir directory("./prudoct_picture/");
    QStringList images = directory.entryList(QStringList() << "*.png" ,QDir::Files);
    QString filename;

    foreach(filename, images) {}

    filename = filename.split(".")[0];

    return (filename.toInt() + 1);
}
