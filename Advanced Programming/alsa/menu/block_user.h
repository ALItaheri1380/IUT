#ifndef BLOCK_USER_H
#define BLOCK_USER_H
#include"persong.h"
#include <QDialog>

namespace Ui {
class block_user;
}

class block_user : public QDialog , public personG
{
    Q_OBJECT

public:
    explicit block_user(QWidget *parent = nullptr);
    ~block_user();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::block_user *ui;
};

#endif // BLOCK_USER_H
