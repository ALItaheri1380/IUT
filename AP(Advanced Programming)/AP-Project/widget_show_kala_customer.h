#ifndef WIDGET_SHOW_KALA_CUSTOMER_H
#define WIDGET_SHOW_KALA_CUSTOMER_H

#include <QWidget>

namespace Ui {
class widget_show_kala_customer;
}

class widget_show_kala_customer : public QWidget
{
    Q_OBJECT

public:
    explicit widget_show_kala_customer(QWidget *parent = nullptr);
    ~widget_show_kala_customer();
    void set(int id ,QString file,QString Name, QString color , int price , int number);
    int getIndex_vector() const;
    void setIndex_vector(int newIndex_vector);

private slots:
    void on_spinBox_valueChanged(int arg1);

    void on_pushButton_change_clicked();

    void on_lineEdit_price_editingFinished();

private:
    Ui::widget_show_kala_customer *ui;
    int id;
    QString Name;
    QString color;
    int price;
    int number;
    QString file;
    int index_vector;
};

#endif // WIDGET_SHOW_KALA_CUSTOMER_H
