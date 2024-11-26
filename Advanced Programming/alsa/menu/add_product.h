#ifndef ADD_PRODUCT_H
#define ADD_PRODUCT_H

#include <QDialog>

namespace Ui {
class Add_Product;
}

class Add_Product : public QDialog
{
    Q_OBJECT

public:
    explicit Add_Product(QWidget *parent = nullptr);
    ~Add_Product();

signals:
    void sendUserName(QString);

private slots:
    void on_pushButton_4_clicked();
    void getUserName(QString str);

    void on_pushButton_5_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::Add_Product *ui;
    QString username;
};

#endif // ADD_PRODUCT_H
