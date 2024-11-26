#ifndef EDITUSER_H
#define EDITUSER_H

#include <QDialog>

namespace Ui {
class EditUser;
}

class EditUser : public QDialog
{
    Q_OBJECT

public:
    explicit EditUser(QWidget *parent = nullptr);
    ~EditUser();
    void set(int ind);

    int getIndex_vector() const;
    void setIndex_vector(int newIndex_vector);

private slots:
    void on_pushButton_Save_clicked();

    void on_pushButton_Delete_clicked();

    void on_pushButton_Ban_clicked();

    void on_pushButton_Cancel_clicked();

private:
    Ui::EditUser *ui;
    int ind;
    int index_vector;
};

#endif // EDITUSER_H
