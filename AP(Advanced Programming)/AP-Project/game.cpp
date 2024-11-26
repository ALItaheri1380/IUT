#include "game.h"
#include "ui_game.h"
#include <QPalette>
#include<windows.h>
#include "Global.h"
#include "client.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(1282,660);
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    ui->label_4->setStyleSheet("background-image: url(:/new/prefix1/golf.png);");
    ui->pushButton->hide();
    ui->progressBar->hide();
    ui->label->hide();
    ui->label_2->hide();
    ui->label_3->hide();
    ui->verticalSlider->hide();
}
bool popo=0;
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_pushButton_clicked()
{
      ui->pushButton->hide();
      ui->verticalSlider->hide();
      ui->progressBar->hide();
      ui->label->setStyleSheet("background-image: url();");
      timer2 = new QTimer (this);
      movie=new QMovie(":/new/prefix1/ezgif.com-gif-maker (1).gif");
      ui->label->setMovie(movie);
      movie->start();
      connect(timer2,SIGNAL(timeout()),this,SLOT(close_this()));
      timer2->start(1245);
      timer1 = new QTimer (this);
      connect(timer1,SIGNAL(timeout()),this,SLOT(update()));
}
bool win=false;
void MainWindow::on_verticalSlider_valueChanged(int value)
{
     ui->progressBar->setValue(value);
     if(0<ui->progressBar->value() && 10>=ui->progressBar->value())
                ui->progressBar->setStyleSheet("QProgressBar::chunk { background-color:rgb(110, 246, 123);}");
     else if(10<ui->progressBar->value() && 20>=ui->progressBar->value())
                ui->progressBar->setStyleSheet("QProgressBar::chunk { background-color:rgb(8, 130, 20);}");
     else if(20<ui->progressBar->value() && 30>=ui->progressBar->value())
                ui->progressBar->setStyleSheet("QProgressBar::chunk { background-color:rgb(255, 241, 63);}");
     else if(30<ui->progressBar->value() && 40>=ui->progressBar->value())
                ui->progressBar->setStyleSheet("QProgressBar::chunk { background-color:rgb(242, 255, 0);}");
     else if(40<ui->progressBar->value() && 50>=ui->progressBar->value())
              ui->progressBar->setStyleSheet("QProgressBar::chunk { background-color:rgb(255, 0, 0);}");
}

void MainWindow::close_this()
{
  timer2->stop();
  timer1->start(15);
  movie->stop();
}

void MainWindow::update()
{
    popo=0;
    if(0<ui->progressBar->value() && 10>=ui->progressBar->value())
    {
        if(ui->label_3->x()<510 && ui->label_3->y() >480)
            ui->label_3->setGeometry(ui->label_3->x()+3,ui->label_3->y()-1, 51, 31);

        else
        {
            if(ui->label_3->x()<680 && ui->label_3->y()<540)
                 ui->label_3->setGeometry(ui->label_3->x()+2,ui->label_3->y()+1, 51, 31);
            else
            {
                ui->label_3->hide();
                ui->label_4->setStyleSheet("background-image: url(:/new/prefix1/game over.png);");
                ui->label_4->show();
                ui->pushButton_2->show();
                ui->label->hide();
                ui->label_2->hide();
            }
        }
    }
    else if(10<ui->progressBar->value() && 20>=ui->progressBar->value())
    {
        if(ui->label_3->x()<700 && ui->label_3->y() >280)
            ui->label_3->setGeometry(ui->label_3->x()+3,ui->label_3->y()-1, 51, 31);

        else
        {
            if(ui->label_3->x()<1010 && ui->label_3->y()<640)
                 ui->label_3->setGeometry(ui->label_3->x()+2,ui->label_3->y()+1, 51, 31);
            else
            {
                ui->label_3->hide();
                ui->label_4->setStyleSheet("background-image: url(:/new/prefix1/game over.png);");
                ui->label_4->show();
                ui->pushButton_2->show();
                ui->label->hide();
                ui->label_2->hide();
            }
        }
    }
    else if(20<ui->progressBar->value() && 30>=ui->progressBar->value())
    {
        if(ui->label_3->x()<770 && ui->label_3->y() >50)
            ui->label_3->setGeometry(ui->label_3->x()+3,ui->label_3->y()-1, 51, 31);
        else
        {
            if(ui->label_3->x()<1100 && ui->label_3->y()<780)
                 ui->label_3->setGeometry(ui->label_3->x()+2,ui->label_3->y()+1, 51, 31);
            else
            {
                popo=1;
                ui->label_3->hide();
                ui->label_4->setStyleSheet("background-image: url(:/new/prefix1/Screenshot_2022-07-07_011802-removebg-preview.png);");
                ui->label_4->show();
                ui->pushButton_2->show();
                ui->label->hide();
                ui->label_2->hide();

            }
        }
    }
    else if(30<ui->progressBar->value() && 40>=ui->progressBar->value())
    {
        if(ui->label_3->x()<800 && ui->label_3->y() >30)
            ui->label_3->setGeometry(ui->label_3->x()+3,ui->label_3->y()-1, 51, 31);

        else
        {
            if(ui->label_3->x()<1200 && ui->label_3->y()<740)
                 ui->label_3->setGeometry(ui->label_3->x()+2,ui->label_3->y()+1, 51, 31);
            else
            {
                ui->label_3->hide();
                ui->label_4->setStyleSheet("background-image: url(:/new/prefix1/game over.png);");
                ui->label_4->show();
                ui->pushButton_2->show();
                ui->label->hide();
                ui->label_2->hide();
            }
        }
    }
    else if(40<ui->progressBar->value() && 50>=ui->progressBar->value())
    {
        ui->label_3->setGeometry(ui->label_3->x()+3,ui->label_3->y()-3, 51, 31);
        if(ui->label_3->x()<1260 && ui->label_3->y()<-5)
        {
            ui->label_4->setStyleSheet("background-image: url(:/new/prefix1/game over.png);");
            ui->label_4->show();
            ui->pushButton_2->show();
            ui->label->hide();
            ui->label_2->hide();
        }
    }
}
void MainWindow::on_pushButton_3_clicked()
{
  ui->label_4->hide();
  ui->pushButton_2->hide();
  ui->pushButton_3->hide();
  ui->pushButton->show();
  ui->progressBar->show();
  ui->label->show();
  ui->label_2->show();
  ui->label_3->show();
  ui->verticalSlider->show();
}

int MainWindow::getIndex_vector() const
{
    return index_vector;
}

void MainWindow::setIndex_vector(int newIndex_vector)
{
    index_vector = newIndex_vector;
}
void MainWindow::on_pushButton_2_clicked()
{
    if(popo)
    {
        Global::Active_person[index_vector].setMoneybags(Global::Active_person[index_vector].get_moneybags()+50);
        for(int i=0;i<Global::vec_person.size();i++)
        {
            if (Global::vec_person[i].get_user_name()==Global::Active_person[index_vector].get_user_name())
            {
                Global::vec_person[i].setMoneybags(Global::Active_person[index_vector].get_moneybags()+50);
            }
        }
    }
    Global::save_all();
    std::string x;
    x="save_"+Global::Active_person[index_vector].get_user_name().toStdString()+".txt";
    std::fstream te(x , std::ios::app);
    te.close();
    std::fstream in(x , std::ios::in);
    if (!in)
        return;
    else
    {
        std::string number,name;
        while (getline(in,number),getline(in ,name))
        {
            Global::Shopping_cart[index_vector].push_back(qMakePair(std::stoi(number) ,std::stoi(name)));
        }
    }
    in.close();
    Client *xx =  new Client(index_vector);
    xx->setIndex_vector(index_vector);
    xx->show();
    this->close();
}

