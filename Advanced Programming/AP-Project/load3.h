#ifndef LOAD3_H
#define LOAD3_H
#include <QTimer>
#include <QDialog>
#include"create_account.h"
namespace Ui {
class load3;
}

class load3 : public QDialog
{
    Q_OBJECT

public:
    explicit load3(QWidget *parent = nullptr);
    ~load3();
    void close_this();

private:
    Ui::load3 *ui;
    QTimer* timer1;
};

#endif // LOAD3_H
