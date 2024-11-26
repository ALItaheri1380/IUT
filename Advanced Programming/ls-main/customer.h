#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <QDialog>
#include <QVector>
#include <cloths.h>
#include <sporting_goods.h>
#include <add_kala.h>
namespace Ui {
class customer;
}

class customer : public QDialog
{
    Q_OBJECT

public:
    explicit customer(int i,QWidget *parent = nullptr);
    ~customer();
    static QVector<cloths> vec_cloths[50];
    static QVector<Sporting_goods> vec_sporting[50];
    static QVector <int> id[50];

    int getSize_of_widget() const;
    void setSize_of_widget(int newSize_of_widget);
    void show_item();
    void refresh();

    int getIndex_vector() const;
    void setIndex_vector(int newIndex_vector);

private slots:
    void on_pushButton_add_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_logout_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void check(int l);

private:
    Ui::customer *ui;
    static int size_of_widget;
    int index_vector;
};

#endif // CUSTOMER_H
