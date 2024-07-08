#ifndef CLOTHING_H
#define CLOTHING_H

#include <QDialog>
#include "product.h"

namespace Ui {
class clothing;
}

class clothing : public QDialog , public product
{
    Q_OBJECT

public:
    explicit clothing(QWidget *parent = nullptr);
    ~clothing();

private slots:
    void on_pushButton_clicked();
    void getUserName(QString str);
    void on_pushButton_3_clicked();
    void on_pushButton_2_clicked();

private:
    Ui::clothing *ui;
    QString size;
    QString type;
};

#endif // CLOTHING_H
