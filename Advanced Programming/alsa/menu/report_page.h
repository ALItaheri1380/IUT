#ifndef REPORT_PAGE_H
#define REPORT_PAGE_H

#include <QDialog>

namespace Ui {
class report_page;
}

class report_page : public QDialog
{
    Q_OBJECT

public:
    explicit report_page(QWidget *parent = nullptr);
    ~report_page();

private slots:
    void getId(QString usern,QString id);
    void on_buttonBox_accepted();

private:
    Ui::report_page *ui;
    QString username;
    QString id;
};

#endif // REPORT_PAGE_H
