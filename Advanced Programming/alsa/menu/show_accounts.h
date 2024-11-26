#ifndef SHOW_ACCOUNTS_H
#define SHOW_ACCOUNTS_H

#include <QDialog>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QSpacerItem>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>

namespace Ui {
class show_accounts;
}

class show_accounts : public QDialog
{
    Q_OBJECT

public:
    explicit show_accounts(QWidget *parent = nullptr);
    ~show_accounts();

private slots:
    void on_pushButton_clicked();
    void getUserName(QString);

private:
    Ui::show_accounts *ui;
    QString type;
    void show_list();

    QSpacerItem* Spacer;
    QVector<QLabel*> labels;

    QVector<QString> liens;

    QVector<QLineEdit*> lineedits;
    QVector<QVBoxLayout*> vlayout;
    QVector<QHBoxLayout*> hlayout;
    QVector<QGroupBox*> groups;
    QVector<QSpacerItem*> spaces;

    QGroupBox *createClientGroup(QString name, QString addres, QString phone, QString card, QString cvv2, QString money);
    QGroupBox *createCustGroup(QString name, QString card, QString cvv2, QString money, QString block);
};

#endif // SHOW_ACCOUNTS_H
