#include "buylist.h"
#include "ui_buylist.h"
#include <QSpacerItem>
#include <QFile>
#include <QMessageBox>
#include "product_detail.h"
#include "postpy.h"
#include "increase_money.h"

buylist::buylist(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::buylist)
{
    ui->setupUi(this);
    setWindowTitle("سبد خرید");
    lay = new QVBoxLayout;
}

buylist::~buylist()
{
    delete ui;

    for(int i = 0; i < spaces.length(); i++)
        delete spaces[i];

    spaces.clear();

    for(int i = 0; i < buttons.length(); i++)
        delete buttons[i];

    buttons.clear();

    for(int i = 0; i < lineedits.length(); i++)
        delete lineedits[i];

    lineedits.clear();

    for(int i = 0; i < labels.length(); i++)
        delete labels[i];

    labels.clear();

    for(int i = 0; i < vlayout.length(); i++)
        delete vlayout[i];

    vlayout.clear();

    for(int i = 0; i < hlayout.length(); i++)
        delete hlayout[i];

    hlayout.clear();

    for(int i = 0; i < spins.length(); i++)
        delete spins[i];

    spins.clear();

    for(int i = 0; i < groups.length(); i++)
        delete groups[i];

    groups.clear();
}

QGroupBox *buylist::createGroup(QString pruduct_id)
{
    setFixedWidth(570);
    setMaximumWidth(570);

    QFile inputFile("prudoct.txt");
    QStringList split;

    if (inputFile.open(QIODevice::ReadOnly))
    {
       QTextStream in(&inputFile);

       for (int i = 0; ; i++)
       {
          QString line = in.readLine();
          split = line.split(",");

          if(split[11] == pruduct_id)
              break;
       }

       inputFile.close();
    }

    QGroupBox *groupBox = new QGroupBox(split[1]);
    groups.push_back(groupBox);

    QHBoxLayout* main_layout = new QHBoxLayout();
    hlayout.push_back(main_layout);

    QLabel* pl = new QLabel{"قیمت نهایی"};
    labels.push_back(pl);

    int fprice = split[2].toInt() * (100 - split[5].toInt());
    QLineEdit* price = new QLineEdit(QString::number(fprice / 100));
    price->setReadOnly(true);
    price->setMaximumWidth(60);
    price->setFixedWidth(60);
    price->setAlignment(Qt::AlignCenter);
    lineedits.push_back(price);

    QLabel* countlabel = new QLabel{"تعداد"};
    labels.push_back(countlabel);

    QSpinBox* count = new QSpinBox;
    count->setMinimumSize(QSize(50,25));
    count->setRange(1,split[3].toInt());
    count->setValue(count_calculate(pruduct_id));
    spins.push_back(count);

    connect(count,SIGNAL(valueChanged(int)),this,SLOT(spin_count_changed(int)));

    QPushButton* remove = new QPushButton{"حذف"};
    QPushButton* detail = new QPushButton{"جزئیات محصول"};
    QString id = pruduct_id;

    connect(remove,&QPushButton::clicked,[this, id] {
        connect(this,SIGNAL(send(QString)),this,SLOT(on_remove_button_clicked(QString)));
        emit send(id);
        });
    connect(detail,&QPushButton::clicked,[this, id] { on_detail_button(id); });

    buttons.push_back(detail);
    buttons.push_back(remove);

    QSpacerItem* Space = new QSpacerItem(60, 0, QSizePolicy::Fixed, QSizePolicy::Fixed);

    main_layout->addWidget(pl);
    main_layout->addWidget(price);
    main_layout->addItem(Space);
    main_layout->addWidget(countlabel);
    main_layout->addWidget(count);
    main_layout->addItem(Space);
    main_layout->addWidget(detail);
    main_layout->addWidget(remove);
    main_layout->setSizeConstraint(QLayout::SetFixedSize);

    groupBox->setLayout(main_layout);
    return groupBox;
}

void buylist::getsId(QString str)
{
    username = str;
    show_list();
}

void buylist::spin_count_changed(int value)
{
    int sum = 0;

    for(int i = 0; i < spins.length(); i++)
    {
        sum += (spins.at(i)->value() * lineedits.at(i)->text().toInt());
    }

    ui->lineEdit_2->setText(QString::number(sum));

    int count = 0;

    QVector<QString> lines;
    QFile inputFile("buylist.txt");
    QStringList split;

    if (inputFile.open(QIODevice::ReadOnly))
    {
       QTextStream in(&inputFile);

       for (int i = 0; !in.atEnd(); i++)
       {
          QString line = in.readLine();

          split = line.split(",");

          if(split[1] == username)
          {
              line = split[0] + "," + username + "," + QString::number(spins.at(count)->value() * lineedits.at(count)->text().toInt()) + "," + QString::number(spins.at(count)->value()) + "," + split[4];
              count++;
          }

          lines.push_back(line);
       }

       inputFile.close();
    }

    QFile file("buylist.txt");
    file.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text);
    QTextStream stream( &file );

    for(int i = 0; i < lines.length(); i++)
        stream << lines.at(i) << "\n";

    file.close();
}

void buylist::on_remove_button_clicked(QString id)
{
    QMessageBox::StandardButton question;

    question = QMessageBox::question(this, "توجه", "آیا میخواهید این کالا را از سبد خرید حذف کنید؟",
                                  QMessageBox::Yes|QMessageBox::No);

    if (question == QMessageBox::No)
        return;

    QVector<QString> lines;
    QFile inputFile("buylist.txt");
    QStringList split;

    if (inputFile.open(QIODevice::ReadOnly))
    {
       QTextStream in(&inputFile);

       for (int i = 0; !in.atEnd(); i++)
       {
          QString line = in.readLine();

          split = line.split(",");

          if(split[4] == id)
              continue;

          lines.push_back(line);
       }

       inputFile.close();
    }

    QFile file("buylist.txt");
    file.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text);
    QTextStream stream( &file );
    for(int i = 0; i < lines.length(); i++)
        stream << lines.at(i) << "\n";

    file.close();

    show_list();
}

void buylist::on_pushButton_2_clicked()
{
    close();
}

void buylist::show_list()
{
    lay->removeItem(Spacer);

    for(int i = 0; i < spins.length(); i++)
         delete spins[i];

    spins.clear();

    for(int i = 0; i < lineedits.length(); i++)
        delete lineedits[i];

    lineedits.clear();

    for(int i = 0; i < groups.length(); i++)
         groups[i]->setVisible(0);

    int count = 0;

    QFile inputFile("buylist.txt");
    QStringList split;

    if (inputFile.open(QIODevice::ReadOnly))
    {
       QTextStream in(&inputFile);

       for (int i = 0; !in.atEnd(); i++)
       {
          QString line = in.readLine();
          split = line.split(",");

          if(split[1] == username && check_customer(split[4]))
          {
              lay->addWidget(createGroup(split[4]));
              count++;
          }
       }

       inputFile.close();
    }

    int sum = 0;

    for(int i = 0; i < spins.length(); i++)
    {
        sum += (spins.at(i)->value() * lineedits.at(i)->text().toInt());
    }

    ui->lineEdit->setText(QString::number(count));
    ui->lineEdit_2->setText(QString::number(sum));

    ui->lineEdit->setAlignment(Qt::AlignCenter);
    ui->lineEdit_2->setAlignment(Qt::AlignCenter);

    Spacer = new QSpacerItem(10, 10, QSizePolicy::Minimum, QSizePolicy::Expanding);
    lay->addSpacerItem(Spacer);
    spaces.push_back(Spacer);

    if(count == 0)
    {
        QMessageBox::information(this,"تایید","سبذ خرید خالی می باشد");
        close();
    }

    ui->scrollArea->setLayout(lay);
}

void buylist::on_detail_button(QString id)
{
    Product_detail* temp = new Product_detail{this};
    connect(this, SIGNAL(sendPruductId(QString)), temp, SLOT(getPruductId(QString)));
    temp->show();

    emit sendPruductId(id);
}

void buylist::on_pushButton_4_clicked()
{
    QFile inputFile("prudoct.txt");
    QStringList split;

    QFile buyfile("buylist.txt");
    QVector<QString> lines;

    if (buyfile.open(QIODevice::ReadOnly))
    {
        QTextStream in1(&buyfile);

        for (int i = 0; !in1.atEnd(); i++)
        {
           QString line1 = in1.readLine();

           if(line1 == "")
              break;

           lines.push_back(line1);
        }

        buyfile.close();
    }

    if (inputFile.open(QIODevice::ReadOnly))
    {
       QTextStream in(&inputFile);

       for (int i = 0; !in.atEnd(); i++)
       {
          QString line = in.readLine();

          split = line.split(",");

          if(line == "")
              break;

          for(int j = 0; j < lines.length(); j++)
          {
              QStringList split1 = lines[j].split(",");

              if(split1[3].toInt() > split[3].toInt() && username == split1[1] && split[11] == split1[4])
              {
                  QMessageBox::warning(this,"اخطار","موجودی کالا کافی نیست");
                  show_list();
                  spin_count_changed(1);
                  return;
              }
          }
       }

       inputFile.close();
    }

    QString dis= "";
    if(Chek == 0){
          PostPy* D = new PostPy(this);
          D->show();
    }
    else
     {
          QFile myfile("C:/Users/digitall home/Documents/Ap/alsa/python files/PostPy.txt");
          if(!myfile.open(QFile::ReadOnly |QFile::Text))
          {
                 qDebug() << " Could not open the file for reading";
           }
          else{
              QTextStream in(&myfile);
              dis = in.readLine();
              myfile.remove();
              myfile.close();
          }
          increase_money* d = new increase_money(this);
          d->show();
          if(dis!=""){
              int n = dis.toFloat();
               qDebug() << " n = "<<n<<Qt::endl;

              int m = ui->lineEdit_2->text().toInt();
              qDebug() << " m= "<<m<<Qt::endl;
              int num = n+m;
              QString Q = QString::number(num);
              connect(this,SIGNAL(add_item(QString,QString)),d,SLOT(add_item(QString,QString)));
              emit  add_item(Q,username);
              close();
          }
          else{
              connect(this,SIGNAL(add_item(QString,QString)),d,SLOT(add_item(QString,QString)));
                emit  add_item(ui->lineEdit_2->text(),username);
          }
       }
    Chek++;
}

bool buylist::check_customer(QString id)
{
    QFile inputFile("prudoct.txt");
    QStringList split;

    if (inputFile.open(QIODevice::ReadOnly))
    {
       QTextStream in(&inputFile);

       for (int i = 0; !in.atEnd(); i++)
       {
          QString line = in.readLine();
          split = line.split(",");

          if(split[11] == id)
              return true;
       }

       inputFile.close();
    }

    return false;
}

int buylist::count_calculate(QString id)
{
    QFile file("buylist.txt");
    QStringList split;

    int count = 1;

    if (file.open(QIODevice::ReadOnly))
    {
       QTextStream in(&file);

       for (int i = 0; !in.atEnd(); i++)
       {
          QString line = in.readLine();
          split = line.split(",");

          if(split[4] == id)
          {
              count = split[3].toInt();
              break;
          }
       }
       file.close();
    }

    return count;
}

void buylist::on_pushButton_3_clicked()
{
    QMessageBox::StandardButton question;

    question = QMessageBox::question(this, "توجه", "آیا میخواهی از سبد خرید را خالی کنید؟",
                                  QMessageBox::Yes|QMessageBox::No);

    if (question == QMessageBox::No)
        return;

    QMessageBox::information(this,"تایید","سبذ خرید با موفقیت خالی شد");
    close();

    QVector<QString> lines;
    QFile inputFile("buylist.txt");
    QStringList split;

    if (inputFile.open(QIODevice::ReadOnly))
    {
       QTextStream in(&inputFile);

       for (int i = 0; !in.atEnd(); i++)
       {
          QString line = in.readLine();

          split = line.split(",");

          if(split[1] == username)
              continue;

          lines.push_back(line);
       }

       inputFile.close();
    }

    QFile file("buylist.txt");
    file.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text);
    QTextStream stream( &file );

    for(int i = 0; i < lines.length(); i++)
        stream << lines.at(i) << "\n";

    file.close();
}
