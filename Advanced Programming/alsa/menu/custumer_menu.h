#ifndef CUSTUMER_MENU_H
#define CUSTUMER_MENU_H

#include <QDialog>

namespace Ui {
class custumer_menu;
}

class custumer_menu : public QDialog
{
    Q_OBJECT

public:
    explicit custumer_menu(QWidget *parent = nullptr);
    ~custumer_menu();

signals:
    void sendUserName(QString);

private slots:
    void on_pushButton_2_clicked();
    void getUserName(QString str);

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::custumer_menu *ui;
    QString username;
};

#endif // CUSTUMER_MENU_H
