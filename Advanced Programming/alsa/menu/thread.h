#ifndef THREAD_H
#define THREAD_H

#include <QDialog>

namespace Ui {
class thread;
}

class thread : public QDialog
{
    Q_OBJECT

public:
    explicit thread(QWidget *parent = nullptr);
    ~thread();

private slots:
    void on_pushButton_clicked();

private:
    Ui::thread *ui;
};

#endif // THREAD_H
