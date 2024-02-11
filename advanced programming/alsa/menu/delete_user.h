#ifndef DELETE_USER_H
#define DELETE_USER_H

#include <QDialog>

namespace Ui {
class delete_user;
}

class delete_user : public QDialog
{
    Q_OBJECT

public:
    explicit delete_user(QWidget *parent = nullptr);
    ~delete_user();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::delete_user *ui;
};

#endif // DELETE_USER_H
