#ifndef REGISTOR_H
#define REGISTOR_H
#include"persong.h"
#include"global_registor.h"
#include <QDialog>

namespace Ui {
class Registor;
}

class Registor : public QDialog,public personG,public global_registor
{
    Q_OBJECT

public:
    explicit Registor(QWidget *parent = nullptr);
    ~Registor();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::Registor *ui;
    void final_regist();
};

#endif // REGISTOR_H
