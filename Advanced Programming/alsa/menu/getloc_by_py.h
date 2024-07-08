#ifndef GETLOC_BY_PY_H
#define GETLOC_BY_PY_H

#include <QDialog>

namespace Ui {
class getLoc_by_py;
}

class getLoc_by_py : public QDialog
{
    Q_OBJECT

public:
    explicit getLoc_by_py(QWidget *parent = nullptr);
    ~getLoc_by_py();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::getLoc_by_py *ui;
    void Write_to_file();
};

#endif // GETLOC_BY_PY_H
