#ifndef DELETE_CLIENT_H
#define DELETE_CLIENT_H

#include <QDialog>
#include"persongclientt.h"
#include"global_chenge_info.h"
namespace Ui {
class delete_client;
}

class delete_client : public QDialog , public personGclientt, public global_chenge_info
{
    Q_OBJECT

public:
    explicit delete_client(QWidget *parent = nullptr);
    ~delete_client();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::delete_client *ui;
};

#endif // DELETE_CLIENT_H
