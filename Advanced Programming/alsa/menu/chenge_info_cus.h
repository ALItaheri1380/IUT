#ifndef CHENGE_INFO_CUS_H
#define CHENGE_INFO_CUS_H
#include"persong.h"
#include"global_chenge_info.h"
#include <QDialog>

namespace Ui {
class chenge_info_cus;
}

class chenge_info_cus : public QDialog,public personG,public global_chenge_info
{
    Q_OBJECT

public:
    explicit chenge_info_cus(QWidget *parent = nullptr);
    ~chenge_info_cus();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::chenge_info_cus *ui;
};

#endif // CHENGE_INFO_CUS_H
