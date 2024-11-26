#ifndef ADVANCED_SEARCH_H
#define ADVANCED_SEARCH_H

#include <QDialog>

namespace Ui {
class advanced_search;
}

class advanced_search : public QDialog
{
    Q_OBJECT

public:
    explicit advanced_search(QWidget *parent = nullptr);
    ~advanced_search();

signals:
    void send_data(QString cat, QString color, QString sort, int state, long long min, long long max, QString info1,QString info2);

private slots:
    void on_comboBox_3_currentIndexChanged(int index);
    void on_buttonBox_accepted();

private:
    Ui::advanced_search *ui;
};

#endif // ADVANCED_SEARCH_H
