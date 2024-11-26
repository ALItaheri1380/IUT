#ifndef POST_PY_H
#define POST_PY_H

#include <QDialog>

namespace Ui {
class Post_py;
}

class Post_py : public QDialog
{
    Q_OBJECT

public:
    explicit Post_py(QWidget *parent = nullptr);
    ~Post_py();

private:
    Ui::Post_py *ui;
};

#endif // POST_PY_H
