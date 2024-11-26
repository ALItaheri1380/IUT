#ifndef ADD_KALA_H
#define ADD_KALA_H

#include <QDialog>

namespace Ui {
class add_kala;
}

class add_kala : public QDialog
{
    Q_OBJECT

public:
    explicit add_kala(QWidget *parent = nullptr);
    ~add_kala();

    int getIndex_vector() const;
    void setIndex_vector(int newIndex_vector);

private slots:
    void on_pushButton_back_clicked();

    void on_pushButton_addphoto_clicked();

    void on_push_buttonconfirm_clicked();

    void on_radioButton_Equipment_clicked();

    void on_radioButton_cloths_clicked();

    void on_checkBox_color_stateChanged(int arg1);

    void on_checkBox_weight_stateChanged(int arg1);

    void on_checkBox_brand_stateChanged(int arg1);

    void on_checkBox_gennder_stateChanged(int arg1);

private:
    Ui::add_kala *ui;
    QString file;
    QString name , color , brand , gender;
    int price , number , weight , type;
    int index_vector;
};

#endif // ADD_KALA_H
