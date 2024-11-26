#ifndef ADMIN_H
#define ADMIN_H

#include <QDialog>
#include "QListWidgetItem"
#include "QVector"
namespace Ui {
class Admin;
}

class Admin : public QDialog
{
    Q_OBJECT

public:
    explicit Admin(int cons,QWidget *parent = nullptr);
    ~Admin();
    void show_item();
    static QVector<int> vec_id_kala;
    void refresh();
    int getIndex_vector() const;
    void setIndex_vector(int newIndex_vector);

private slots:
    void on_listWidget_user_itemDoubleClicked(QListWidgetItem *item);

    void on_listWidget_commodity_itemDoubleClicked(QListWidgetItem *item);

    void on_pushButton_log_out_clicked();

    void on_pushButton_clicked();

private:
    Ui::Admin *ui;
    int index_vector;
};

#endif // ADMIN_H
