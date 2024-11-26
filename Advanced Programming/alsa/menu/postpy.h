#ifndef POSTPY_H
#define POSTPY_H

#include <QDialog>

namespace Ui {
class PostPy;
}

class PostPy : public QDialog
{
    Q_OBJECT

public:
    explicit PostPy(QWidget *parent = nullptr);
    ~PostPy();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::PostPy *ui;
};

#endif // POSTPY_H
