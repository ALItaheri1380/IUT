#ifndef FACTOR_H
#define FACTOR_H

#include <QDockWidget>
#include "QVector"
namespace Ui {
class factor;
}

class factor : public QDockWidget
{
    Q_OBJECT

public:
    explicit factor(int in,QWidget *parent = nullptr);
    ~factor();
    void show_item(int index);

    int getIndex_vector() const;
    void setIndex_vector(int newIndex_vector);

private slots:
    void on_pushButton_next_clicked();

    void on_pushButton_previous_clicked();


private:
    Ui::factor *ui;
    QVector <int> ind;
    int now{0};
    int index_vector;
};

#endif // FACTOR_H
