#ifndef MARKAZ_H
#define MARKAZ_H

#include <QDialog>

namespace Ui {
class markaz;
}

class markaz : public QDialog
{
    Q_OBJECT

public:
    explicit markaz(QWidget *parent = nullptr);
    ~markaz();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_13_clicked();

private:
    Ui::markaz *ui;
};

#endif // MARKAZ_H
