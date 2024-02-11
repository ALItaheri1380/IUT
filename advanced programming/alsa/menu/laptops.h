#ifndef LAPTOPS_H
#define LAPTOPS_H

#include <QDialog>
#include "product.h"

namespace Ui {
class laptops;
}

class laptops : public QDialog , public product
{
    Q_OBJECT

public:
    explicit laptops(QWidget *parent = nullptr);
    ~laptops();

private slots:
    void on_pushButton_clicked();
    void getUserName(QString str);
    void on_pushButton_3_clicked();
    void on_pushButton_2_clicked();

private:
    Ui::laptops *ui;
    double space{0};
    int ram{0};
};

#endif // LAPTOPS_H
