#ifndef CLIENT_MENO_H
#define CLIENT_MENO_H

#include <QDialog>
#include "list_pruduct.h"
//#include "increase_money.h"

namespace Ui {
class client_meno;
}

class client_meno : public QDialog
{
    Q_OBJECT

public:
    explicit client_meno(QWidget *parent = nullptr);
    ~client_meno();

signals:
    void sendUserName(QString);
    void sendPruductId(QString);

private slots:
    void on_pushButton_clicked();
    void on_pushButton_4_clicked();
    void getUserName(QString str);

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_exit_clicked();

private:
    Ui::client_meno *ui;
    QString username;
};

#endif // CLIENT_MENO_H
