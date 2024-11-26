#ifndef WIDGET_USER_H
#define WIDGET_USER_H

#include <QWidget>

namespace Ui {
class widget_user;
}

class widget_user : public QWidget
{
    Q_OBJECT

public:
    explicit widget_user(QWidget *parent = nullptr);
    ~widget_user();
    void set(QString x);

    int getIndex_vector() const;
    void setIndex_vector(int newIndex_vector);

private:
    Ui::widget_user *ui;
    QString user_name{""};
    int index_vector;
};

#endif // WIDGET_USER_H
