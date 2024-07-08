#ifndef LIST_PRUDUCT_H
#define LIST_PRUDUCT_H

#include <QDialog>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QLineEdit>
#include <QComboBox>

class list_pruduct : public QDialog
{
    Q_OBJECT

public:
    list_pruduct(QWidget *parent = nullptr);
    ~list_pruduct();
    int countlines(QString fname);

signals:
    void sendId(QString,QString);
    void sendPruductId(QString);

private slots:
    void on_buy_button(QString id);
    void on_detail_button(QString id);
    void get_end(QString);
    void on_report_button(QString id);
    void on_remove_button(QString id);
    void on_edit_button(QString id);
    void on_back_button();
    void on_next_button();
    void on_privious_button();
    void getUserName(QString str);
    void on_buy_list_button();
    void combo_changed(int);
    void search_changed(QString str);
    void on_advanced_search_clicked();
    void advanced_search_get(QString cat, QString color, QString sort, int state, long long min, long long max, QString info1,QString info2);

private:
    QString username;
    QString type;
    int comboindex{0};

    void sort(QString typr);
    void creat_button_lay(QVBoxLayout *, QString id);
    QGroupBox* createGroup(int index);
    QGroupBox* createEmptyGroup();

    QVector<QPushButton*> buttons;
    QVector<QLabel*> labels;
    QVector<QLineEdit*> lineedits;
    QVector<QVBoxLayout*> vlayout;
    QVector<QHBoxLayout*> hlayout;
    QVector<QGroupBox*> groups;

    QVector<QString> lines;
    QVector<QString> ids;

    QGridLayout *grid;

    static int number;
    void show_list(int i);
    void read(QString cust_name,
              QString name,
              long long min,
              long long max,
              int count,
              QString color,
              QString info1 = "all",
              QString info2 = "all",
              QString categ = "A");

    QHBoxLayout* button_lay;
    QHBoxLayout* search_lay;
    QHBoxLayout* page_lay;

    QPushButton* buy;
    QPushButton* detail;
    QPushButton* report;
    QPushButton* remove;
    QPushButton* edit;
    QPushButton* back;
    QPushButton* next;
    QPushButton* buy_list;
    QPushButton* privious;
    QLineEdit* page_number;
    QLineEdit* search;
    QPushButton* advance_search;
    QLabel* numbers;
    QComboBox* categorate;
    QSpacerItem* space;
};

#endif // LIST_PRUDUCT_H
