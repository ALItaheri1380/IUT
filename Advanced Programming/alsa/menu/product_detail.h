#ifndef PRODUCT_DETAIL_H
#define PRODUCT_DETAIL_H

#include <QDialog>

namespace Ui {
class Product_detail;
}

class Product_detail : public QDialog
{
    Q_OBJECT

public:
    explicit Product_detail(QWidget *parent = nullptr);
    ~Product_detail();

private slots:
    void on_pushButton_clicked();
    void getPruductId(QString str);

    void on_pushButton_2_clicked();

private:
    Ui::Product_detail *ui;
    QString id;
};

#endif // PRODUCT_DETAIL_H
