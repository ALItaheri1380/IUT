#ifndef INCREASE_MONEY_H
#define INCREASE_MONEY_H
#include <QDialog>
#include"persong.h"
#include"persongclientt.h"
#include"global_payment.h"
namespace Ui {
class increase_money;
}

class increase_money : public QDialog,public personGclientt,public personG,public global_Payment
{
    Q_OBJECT

public:
    explicit increase_money(QWidget *parent = nullptr);
    ~increase_money();

private slots:

    void add_money(QString);

    void on_buttonBox_accepted();

    void add_item(QString,QString);
private:
    Ui::increase_money *ui;
private:
    void Write_to_file_remove();
    void Read_file_buylist();
    void Write_to_file_history();
    void Read_file_history();
    void increas_money_of_customer();
    QString username;
    QVector<QString> customer_name;
    QVector<QString> client_name;
    QVector<QString> price;
    QVector<QString> counter;
    QVector<QString> customer_name_his;
    QVector<QString> client_name_his;
    QVector<QString> price_his;
    QVector<QString> counter_his;
    QVector<QString> customer_name_remove;
    QVector<QString> client_name_remove;
    QVector<QString> price_remove;
    QVector<QString> counter_remove;
    QVector<QString> id_remove;
    QVector<QString> id;
/**************************************************/
    QVector<QString>n_cl;
    QVector<QString>n_pr;
    QVector<QString>n_price;
    QVector<QString>n_num;
    QVector<QString>n_col;
    QVector<QString>n_dis;
    QVector<QString>n_seen;
    QVector<QString>n_num_buy;
    QVector<QString>n_glob1;
    QVector<QString>n_glob2;
    QVector<QString>n_exp;
    QVector<QString>n_id;
    QVector<QString>n_w;
    void Read_file_prd();
    void Write_to_file_prd();
/***************************************************/
    bool check_buy = false;
    void increas();
};

#endif // INCREASE_MONEY_H
