#ifndef REPORTS_H
#define REPORTS_H

#include <QDialog>
#include <QGroupBox>
#include <QSpacerItem>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QLabel>
#include "persong.h"

namespace Ui {
class reports;
}

class reports : public QDialog , public personG
{
    Q_OBJECT

public:
    explicit reports(QWidget *parent = nullptr);
    ~reports();

protected slots:
    void on_detail_button(QString id);
    void on_accept_button(QString id);
    void on_ignore_button(QString id);


signals:
    void sendPruductId(QString);
private:
    Ui::reports *ui;
    QString customer(QString id);

    QGroupBox *createGroup(QString name, QString _type, QString details, QString id);

    void show_list();

    QSpacerItem* Spacer;
    QVector<QLabel*> labels;

    QVector<QString> liens;
    QVector<QPushButton*> buttons;
    QVector<QLineEdit*> lineedits;
    QVector<QHBoxLayout*> hlayout;
    QVector<QGroupBox*> groups;
    QVector<QSpacerItem*> spaces;
};

#endif // REPORTS_H
