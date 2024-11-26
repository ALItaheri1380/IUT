#ifndef TEST_H
#define TEST_H

#include <QDialog>

namespace Ui {
class test;
}

class test : public QDialog
{
    Q_OBJECT

public:
    explicit test(QWidget *parent = nullptr);
    ~test();

private:
    Ui::test *ui;
};

#endif // TEST_H
