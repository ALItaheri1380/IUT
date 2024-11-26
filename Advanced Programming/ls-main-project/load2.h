#ifndef LOAD2_H
#define LOAD2_H

#include <QDialog>

namespace Ui {
class load2;
}

class load2 : public QDialog
{
    Q_OBJECT

public:
    explicit load2(QWidget *parent = nullptr);
    ~load2();

private:
    Ui::load2 *ui;
};

#endif // LOAD2_H
