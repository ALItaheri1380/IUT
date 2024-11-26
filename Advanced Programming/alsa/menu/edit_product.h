#ifndef EDIT_PRODUCT_H
#define EDIT_PRODUCT_H

#include <QDialog>

namespace Ui {
class Edit_product;
}

class Edit_product : public QDialog
{
    Q_OBJECT

public:
    explicit Edit_product(QWidget *parent = nullptr);
    ~Edit_product();

signals:
    void show_end(QString);

private slots:
    void getPruductId(QString str);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::Edit_product *ui;
    QString id;
    QPixmap imagePixmap;
};

#endif // EDIT_PRODUCT_H
