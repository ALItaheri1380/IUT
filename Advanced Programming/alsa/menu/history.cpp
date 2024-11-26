#include "history.h"
#include "ui_history.h"
#include <QFile>

history::history(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::history)
{
    ui->setupUi(this);
    setWindowTitle("تاریخچه");
}

history::~history()
{
    delete ui;

    for(int i = 0; i < spaces.length(); i++)
        delete spaces[i];

    spaces.clear();

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

    for(int i = 0; i < groups.length(); i++)
        delete groups[i];

    groups.clear();
}

void history::getsId(QString str)
{
    username = str;

    QFile inputFile("history.txt");
    QStringList split;

    if (inputFile.open(QIODevice::ReadOnly))
    {
       QTextStream in(&inputFile);

       for (int i = 0; !in.atEnd(); i++)
       {
          QString line = in.readLine();
          liens.push_front(line);
       }

       inputFile.close();
    }

    if(username == "admin")
    {
        type = username;
        show_list();
        return;
    }

    QFile myfile("Login_customer.txt");
    if(!myfile.open(QFile::ReadOnly |QFile::Text))
    {
       return;
    }

    QTextStream  in(&myfile);
    while (!in.atEnd())
    {
        QString myText = in.readLine();
        QStringList List = myText.split(',');
        if(username == List[0])
        {
            username = List[0];
            type = List[0];
            show_list();
            return;
        }
    }

    myfile.close();
    type = "client";

    show_list();
}

QGroupBox* history::createGroup(QString cust, QString clien, long long price, int c)
{
    QGroupBox *groupBox = new QGroupBox;
    groups.push_back(groupBox);

    QHBoxLayout* main_layout = new QHBoxLayout();
    hlayout.push_back(main_layout);

    QLabel* pl = new QLabel{"قیمت"};
    labels.push_back(pl);
    QLabel* count_label = new QLabel{"تعداد"};
    labels.push_back(pl);
    QLabel* cust_label = new QLabel{"فروشنده"};
    labels.push_back(pl);
    QLabel* client_label = new QLabel{"خریدار"};
    labels.push_back(pl);

    QLineEdit* price1 = new QLineEdit(QString::number(price));
    price1->setReadOnly(true);
    price1->setMaximumWidth(65);
    price1->setFixedWidth(65);
    price1->setAlignment(Qt::AlignCenter);
    lineedits.push_back(price1);

    QLineEdit* custumer = new QLineEdit(cust);
    custumer->setReadOnly(true);
    custumer->setMaximumWidth(60);
    custumer->setFixedWidth(60);
    custumer->setAlignment(Qt::AlignCenter);
    lineedits.push_back(custumer);

    QLineEdit* client = new QLineEdit(clien);
    client->setReadOnly(true);
    client->setMaximumWidth(60);
    client->setFixedWidth(60);
    client->setAlignment(Qt::AlignCenter);
    lineedits.push_back(client);

    QLineEdit* count = new QLineEdit(QString::number(c));
    count->setReadOnly(true);
    count->setMaximumWidth(30);
    count->setFixedWidth(30);
    count->setAlignment(Qt::AlignCenter);
    lineedits.push_back(count);

    QLabel* countlabel = new QLabel{"تعداد"};
    labels.push_back(countlabel);

    QSpacerItem* Space = new QSpacerItem(20, 0, QSizePolicy::Fixed, QSizePolicy::Fixed);

    main_layout->addWidget(cust_label);
    main_layout->addWidget(custumer);
    main_layout->addItem(Space);

    main_layout->addWidget(client_label);
    main_layout->addWidget(client);
    main_layout->addItem(Space);

    main_layout->addWidget(pl);
    main_layout->addWidget(price1);
    main_layout->addItem(Space);

    main_layout->addWidget(count_label);
    main_layout->addWidget(count);

    main_layout->setSizeConstraint(QLayout::SetFixedSize);

    groupBox->setLayout(main_layout);
    return groupBox;
}

void history::show_list()
{
   for (int i = 0; i < liens.length(); i++)
   {
      QStringList split = liens[i].split(",");

      if(username != "admin")
      {
         if(split[0] == username || split[1] == username)
         {
             if(type == "client")
                 ui->verticalLayout->addWidget(createGroup(split[0], "شما", split[2].toLongLong(), split[3].toInt()));

             else
                 ui->verticalLayout->addWidget(createGroup("شما", split[1], split[2].toLongLong(), split[3].toInt()));
          }
      }

      else
      {
          ui->verticalLayout->addWidget(createGroup(split[0], split[1], split[2].toLongLong(), split[3].toInt()));
      }
   }

    ui->verticalLayout->setAlignment(Qt::AlignCenter);

    QSpacerItem* space = new QSpacerItem(10, 10, QSizePolicy::Minimum, QSizePolicy::Expanding);
    ui->verticalLayout->addSpacerItem(space);
    spaces.push_back(space);
}

void history::on_pushButton_2_clicked()
{
    close();
}

