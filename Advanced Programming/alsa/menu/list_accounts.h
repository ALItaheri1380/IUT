#ifndef LIST_ACCOUNTS_H
#define LIST_ACCOUNTS_H

#include <QDialog>

namespace Ui {
class list_accounts;
}

class list_accounts : public QDialog
{
    Q_OBJECT

public:
    explicit list_accounts(QWidget *parent = nullptr);
    ~list_accounts();

private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

signals:
    void sendUserName(QString);

private:
    Ui::list_accounts *ui;
};

#endif // LIST_ACCOUNTS_H
