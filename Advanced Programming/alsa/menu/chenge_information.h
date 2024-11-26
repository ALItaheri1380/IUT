#ifndef CHENGE_INFORMATION_H
#define CHENGE_INFORMATION_H

#include <QDialog>

namespace Ui {
class chenge_information;
}

class chenge_information : public QDialog
{
    Q_OBJECT

public:
    explicit chenge_information(QWidget *parent = nullptr);
    ~chenge_information();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::chenge_information *ui;
};

#endif // CHENGE_INFORMATION_H
