#ifndef BUYLIST_H
#define BUYLIST_H

#include <QDialog>
#include <QGroupBox>
#include <QDialog>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QLineEdit>
#include <QSpinBox>

namespace Ui {
class buylist;
}

class buylist : public QDialog
{
    Q_OBJECT

public:
    explicit buylist(QWidget *parent = nullptr);
    ~buylist();

signals:
    void sendPruductId(QString id);
    void add_item(QString,QString);
    void send(QString);

private slots:
    void getsId(QString str);
    void spin_count_changed(int value);
    void on_remove_button_clicked(QString id);
    void show_list();
    void on_detail_button(QString id);
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    bool check_customer(QString id);

private:
    int count_calculate(QString id);
    int Chek = 0;
    QString username;

    QGroupBox* createGroup(QString pruduct_id);

    Ui::buylist *ui;

    QVBoxLayout* lay;
    QSpacerItem* Spacer;
    QVector<QPushButton*> buttons;
    QVector<QLabel*> labels;
    QVector<QLineEdit*> lineedits;
    QVector<QVBoxLayout*> vlayout;
    QVector<QHBoxLayout*> hlayout;
    QVector<QGroupBox*> groups;
    QVector<QSpinBox*> spins;
    QVector<QSpacerItem*> spaces;
};

#endif // BUYLIST_H
