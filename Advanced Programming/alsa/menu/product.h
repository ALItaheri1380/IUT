#ifndef PRODUCT_H
#define PRODUCT_H
#include <QWidget>
#include <QFileDialog>

class product
{
public:
    product();

protected:
    QString name;
    QString coloer;
    int count{0};
    QString price{"0"};
    QString username;
    QPixmap imagePixmap;
    QString otherDetail;

    static int countlines(QString filename);

    virtual void on_pushButton_clicked() = 0;
    int photo_name();
};

#endif // PRODUCT_H
