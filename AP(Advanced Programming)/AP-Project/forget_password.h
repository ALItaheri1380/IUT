#ifndef FORGET_PASSWORD_H
#define FORGET_PASSWORD_H

#include <QDialog>

namespace Ui {
class forget_password;
}

class forget_password : public QDialog
{
    Q_OBJECT

public:
    explicit forget_password(QWidget *parent = nullptr);
    ~forget_password();

    int getIndex_vector() const;
    void setIndex_vector(int newIndex_vector);

private slots:
    void on_buttonBox_accepted();

private:
    Ui::forget_password *ui;
    int index_vector;
};

#endif // FORGET_PASSWORD_H
