#ifndef ADD_TO_CART_H
#define ADD_TO_CART_H

#include <QDialog>

namespace Ui {
class add_to_cart;
}

class add_to_cart : public QDialog
{
    Q_OBJECT

public:
    explicit add_to_cart(QWidget *parent = nullptr);
    ~add_to_cart();
    void set(int id);
    void admin();

    int getIndex_vector() const;
    void setIndex_vector(int newIndex_vector);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::add_to_cart *ui;
    int id;
    int index_vector;
};

#endif // ADD_TO_CART_H
