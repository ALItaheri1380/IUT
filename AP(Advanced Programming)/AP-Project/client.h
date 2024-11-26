#ifndef CLIENT_H
#define CLIENT_H

#include <QDialog>
#include "QVector"
#include "article.h"
#include "sporting_goods.h"
#include "cloths.h"
#include "QListWidgetItem"
namespace Ui {
class Client;
}

class Client : public QDialog
{
    Q_OBJECT

public:
    explicit Client(int ind_cons,QWidget *parent = nullptr);
    void serch(QString name="" , int min=0 , int max=100000000 , QString color="" , QString brand="" , QString weight="",QString qtype="",QString gender="");
    void set();

    void show_item();
    void add_global_to_item_widget();
    int count{0};

    void refrsh();

    ~Client();


    int getIndex_vector() const;
    void setIndex_vector(int newIndex_vector);

private slots:
    void on_pushButton_logout_clicked();

    void on_pushButton_Cart_clicked();

    void on_pushButton_moneybags_clicked();

    void on_pushButton_serch_clicked();

    //void on_spinBox_max_editingFinished();

    //void on_spinBox_min_editingFinished();

    void on_listWidget_commodity_itemDoubleClicked(QListWidgetItem *item);

    void on_comboBox_coler_currentTextChanged(const QString &arg1);

    void on_comboBox_brand_currentTextChanged(const QString &arg1);

    void on_comboBox_Weight_currentTextChanged(const QString &arg1);

    void on_comboBox_type_currentTextChanged(const QString &arg1);

    void on_comboBox_sex_currentTextChanged(const QString &arg1);

    void on_spinBox_max_valueChanged(int arg1);

    void on_spinBox_min_valueChanged(int arg1);

    void on_pushButton_clicked();

private:
    Ui::Client *ui;
    QString Name{""};
    int Min{0};
    int Max{100000000};
    QString Color{""};
    QString Brand{""};
    QString Weight{""};
    QString Type{""};
    QString Gender{""};
    QVector <Sporting_goods> item_widget_sporting;
    QVector <cloths> item_widget_cloths;
    static QVector <int> id[50];
    int index_vector;
};


#endif // CLIENT_H
