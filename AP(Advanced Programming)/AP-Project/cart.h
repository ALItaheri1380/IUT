#ifndef CART_H
#define CART_H

#include <QDialog>

namespace Ui {
class Cart;
}

class Cart : public QDialog
{
    Q_OBJECT

public:
    explicit Cart(int cons5,QWidget *parent = nullptr);
    ~Cart();

    int getIndex_vector() const;
    void setIndex_vector(int newIndex_vector);

private slots:
    void on_pushButton_close_clicked();
    void on_pushButton_romove_clicked();
    void on_pushButton_buy_clicked();

private:
    Ui::Cart *ui;
    void show_item();
    int sum=0;
    int index_vector;

};

#endif // CART_H
