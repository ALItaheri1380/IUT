#ifndef LOAD1_H
#define LOAD1_H
#include <QDialog>
#include <QTimer>
#include "Global.h"
namespace Ui {
class load1;
}

class load1 : public QDialog
{
    Q_OBJECT

public:
    explicit load1(QWidget *parent = nullptr);
    ~load1();
private slots:
    void close_this();
    void updat();
private:
    Ui::load1 *ui;
    QTimer* timer1;
    QTimer* timer2;
};


#endif // LOAD1_H
