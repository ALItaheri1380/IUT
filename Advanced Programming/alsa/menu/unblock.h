#ifndef UNBLOCK_H
#define UNBLOCK_H
#include"persong.h"
#include <QDialog>

namespace Ui {
class unblock;
}

class unblock : public QDialog,public personG
{
    Q_OBJECT

public:
    explicit unblock(QWidget *parent = nullptr);
    ~unblock();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::unblock *ui;
};

#endif // UNBLOCK_H
