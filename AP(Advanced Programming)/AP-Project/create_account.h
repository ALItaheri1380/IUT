#ifndef CREATE_ACCOUNT_H
#define CREATE_ACCOUNT_H

#include <QDialog>
#include "Global.h"
namespace Ui {
class Create_account;
}

class Create_account : public QDialog
{
    Q_OBJECT

public:
    explicit Create_account(QWidget *parent = nullptr);
    ~Create_account();

    int getIndex_vector() const;
    void setIndex_vector(int newIndex_vector);

private slots:
    void on_buttonBox_accepted();

private:
    Ui::Create_account *ui;
    int index_vector;

};

#endif // CREATE_ACCOUNT_H
