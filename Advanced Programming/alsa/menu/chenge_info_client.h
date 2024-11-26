#ifndef CHENGE_INFO_CLIENT_H
#define CHENGE_INFO_CLIENT_H
#include"persongclientt.h"
#include"global_chenge_info.h"
#include <QDialog>
namespace Ui {
class chenge_info_client;
}

class chenge_info_client : public QDialog, public personGclientt, public global_chenge_info
{
    Q_OBJECT

public:
    explicit chenge_info_client(QWidget *parent = nullptr);
    ~chenge_info_client();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::chenge_info_client *ui;
};

#endif // CHENGE_INFO_CLIENT_H
