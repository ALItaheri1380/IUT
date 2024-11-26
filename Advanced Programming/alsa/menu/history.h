#ifndef HISTORY_H
#define HISTORY_H

#include <QDialog>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QSpacerItem>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>

namespace Ui {
class history;
}

class history : public QDialog
{
    Q_OBJECT

public:
    explicit history(QWidget *parent = nullptr);
    ~history();

private slots:
    void getsId(QString str);

    void on_pushButton_2_clicked();

private:
    Ui::history *ui;
    QString username;
    QString type;
    QGroupBox *createGroup(QString cust, QString clien, long long price, int c);

    void show_list();

    QSpacerItem* Spacer;
    QVector<QLabel*> labels;

    QVector<QString> liens;

    QVector<QLineEdit*> lineedits;
    QVector<QVBoxLayout*> vlayout;
    QVector<QHBoxLayout*> hlayout;
    QVector<QGroupBox*> groups;
    QVector<QSpacerItem*> spaces;
};

#endif // HISTORY_H
