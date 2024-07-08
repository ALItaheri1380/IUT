#include "post_py.h"
#include "ui_post_py.h"

Post_py::Post_py(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Post_py)
{
    ui->setupUi(this);
}

Post_py::~Post_py()
{
    delete ui;
}
