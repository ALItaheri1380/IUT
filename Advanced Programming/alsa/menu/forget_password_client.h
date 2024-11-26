#ifndef FORGET_PASSWORD_CLIENT_H
#define FORGET_PASSWORD_CLIENT_H
#include"global_forgetpassword.h"
#include "persongclientt.h"
#include <QDialog>

namespace Ui {
class forget_password_client;
}

class forget_password_client : public QDialog,public personGclientt,public global_forgetPassword
{
    Q_OBJECT

public:
    explicit forget_password_client(QWidget *parent = nullptr);
    ~forget_password_client();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::forget_password_client *ui;
};

#endif // FORGET_PASSWORD_CLIENT_H
