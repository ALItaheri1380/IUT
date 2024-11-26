#ifndef WIDGET_TRANSACTIONS_H
#define WIDGET_TRANSACTIONS_H

#include <QWidget>

namespace Ui {
class widget_transactions;
}

class widget_transactions : public QWidget
{
    Q_OBJECT

public:
    explicit widget_transactions(QWidget *parent = nullptr);
    ~widget_transactions();
    void set(int price , QString username , QString type , QString Date);

    int getIndex_vector() const;
    void setIndex_vector(int newIndex_vector);

private:
    Ui::widget_transactions *ui;
    int index_vector;
};

#endif // WIDGET_TRANSACTIONS_H
