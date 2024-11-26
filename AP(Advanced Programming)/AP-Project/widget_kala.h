#ifndef WIDGET_KALA_H
#define WIDGET_KALA_H

#include <QWidget>
namespace Ui {
class widget_kala;
}

class widget_kala : public QWidget
{
    Q_OBJECT

public:
    explicit widget_kala(QWidget *parent = nullptr);
    ~widget_kala();
    void set(QString phonto , QString name , QString color , int price);

    int getIndex_vector() const;
    void setIndex_vector(int newIndex_vector);

private:
    Ui::widget_kala *ui;
    int index_vector;

};

#endif // WIDGET_KALA_H
