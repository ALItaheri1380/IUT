#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include "Global.h"
namespace Ui {
class login;
}

class login : public QDialog
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    void check_correct_password(QString user_name,QString password);
    ~login();


private slots:
    void on_pushButton_Creat_clicked();

    void on_commandLinkButton_clicked();

    void on_pushButton_Login_clicked();

private:
    Ui::login *ui;
    int sum;
};

#endif // LOGIN_H
