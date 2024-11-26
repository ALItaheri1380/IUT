#ifndef WATCHES_H
#define WATCHES_H

#include <QDialog>
#include "product.h"

namespace Ui {
class watches;
}

class watches : public QDialog , public product
{
    Q_OBJECT

public:
    explicit watches(QWidget *parent = nullptr);
    ~watches();

private slots:
    void on_pushButton_clicked();
    void getUserName(QString str);
    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::watches *ui;
    QString brand;
    QString type;
};

#endif // WATCHES_H
