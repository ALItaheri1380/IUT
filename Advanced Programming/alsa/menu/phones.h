#ifndef PHONES_H
#define PHONES_H

#include <QDialog>
#include "product.h"

namespace Ui {
class phones;
}

class phones : public QDialog , public product
{
    Q_OBJECT

public:
    explicit phones(QWidget *parent = nullptr);
    ~phones();

private slots:
    void on_pushButton_clicked();
    void getUserName(QString str);
    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::phones *ui;
    double space{0};
    int android{0};
};

#endif // PHONES_H
