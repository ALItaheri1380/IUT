#ifndef DELETE_CUS_H
#define DELETE_CUS_H
#include"persong.h"
#include"global_chenge_info.h"
#include <QDialog>

namespace Ui {
class delete_cus;
}

class delete_cus : public QDialog , public personG , public global_chenge_info
{
    Q_OBJECT

public:
    explicit delete_cus(QWidget *parent = nullptr);
    ~delete_cus();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::delete_cus *ui;
};

#endif // DELETE_CUS_H
