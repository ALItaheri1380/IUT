#include "show_accounts.h"
#include "ui_show_accounts.h"
#include <QFile>

show_accounts::show_accounts(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::show_accounts)
{
    ui->setupUi(this);
    setWindowTitle("لیست اکانت ها");
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
}

show_accounts::~show_accounts()
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

QGroupBox* show_accounts::createClientGroup(QString name, QString addres, QString phone, QString card, QString cvv2, QString money)
{
    QGroupBox *groupBox = new QGroupBox;
    groups.push_back(groupBox);

    QHBoxLayout* main_layout = new QHBoxLayout();
    hlayout.push_back(main_layout);

    QLineEdit* nam = new QLineEdit{name};
    lineedits.push_back(nam);
    nam->setReadOnly(1);
    nam->setMaximumWidth(60);

    QLineEdit* addr = new QLineEdit{addres};
    lineedits.push_back(addr);
    addr->setMaximumWidth(140);
    addr->setReadOnly(1);

    QLineEdit* phon = new QLineEdit{phone};
    lineedits.push_back(phon);
    phon->setMaximumWidth(60);
    phon->setReadOnly(1);

    QLineEdit* Card = new QLineEdit{card};
    lineedits.push_back(Card);
    Card->setMaximumWidth(60);
    Card->setReadOnly(1);

    QLineEdit* cvv = new QLineEdit{cvv2};
    lineedits.push_back(cvv);
    cvv->setMaximumWidth(60);
    cvv->setReadOnly(1);

    QLineEdit* moneyy = new QLineEdit{money};
    lineedits.push_back(moneyy);
    moneyy->setMaximumWidth(70);
    moneyy->setReadOnly(1);

    QSpacerItem* Space = new QSpacerItem(20, 0, QSizePolicy::Fixed, QSizePolicy::Fixed);

    main_layout->addWidget(nam);
    main_layout->addItem(Space);

    main_layout->addWidget(addr);
    main_layout->addItem(Space);

    main_layout->addWidget(phon);
    main_layout->addItem(Space);

    main_layout->addWidget(Card);
    main_layout->addItem(Space);

    main_layout->addWidget(cvv);
    main_layout->addItem(Space);

    main_layout->addWidget(moneyy);

    groupBox->setLayout(main_layout);
    groupBox->setMaximumWidth(560);

    return groupBox;
}

QGroupBox *show_accounts::createCustGroup(QString name, QString card, QString cvv2, QString money, QString block)
{
    QGroupBox *groupBox = new QGroupBox;
    groups.push_back(groupBox);

    QHBoxLayout* main_layout = new QHBoxLayout();
    hlayout.push_back(main_layout);

    QLineEdit* nam = new QLineEdit{name};
    lineedits.push_back(nam);
    nam->setReadOnly(1);
    nam->setMaximumWidth(60);

    QLineEdit* cards = new QLineEdit{card};
    lineedits.push_back(cards);
    cards->setMaximumWidth(60);
    cards->setReadOnly(1);

    QLineEdit* moneys = new QLineEdit{money};
    lineedits.push_back(moneys);
    moneys->setMaximumWidth(60);
    moneys->setReadOnly(1);

    QLineEdit* cvv = new QLineEdit{cvv2};
    lineedits.push_back(cvv);
    cvv->setMaximumWidth(60);
    cvv->setReadOnly(1);

    QLineEdit* blocks = new QLineEdit{block};
    lineedits.push_back(blocks);
    blocks->setMaximumWidth(70);
    blocks->setReadOnly(1);

    QSpacerItem* Space = new QSpacerItem(20, 0, QSizePolicy::Fixed, QSizePolicy::Fixed);

    main_layout->addWidget(nam);
    main_layout->addItem(Space);

    main_layout->addWidget(cards);
    main_layout->addItem(Space);

    main_layout->addWidget(cvv);
    main_layout->addItem(Space);

    main_layout->addWidget(moneys);
    main_layout->addItem(Space);

    main_layout->addWidget(blocks);

    groupBox->setLayout(main_layout);
    groupBox->setMaximumWidth(560);

    return groupBox;
}

void show_accounts::show_list()
{
    QStringList split;

    if(type == "client")
    {
        QFile inputFile("Login_client.txt");
        QStringList split;

        if (inputFile.open(QIODevice::ReadOnly))
        {
           QTextStream in(&inputFile);

           for (int i = 0; !in.atEnd(); i++)
           {
              QString line = in.readLine();

              if(line == "")
                  break;

              split = line.split(",");
              ui->verticalLayout->addWidget(createClientGroup(split[0], split[2], split[3],split[4],split[5],split[6]));
           }

           inputFile.close();
        }
    }

    else
    {
        QFile inputFile("Login_customer.txt");
        QStringList split;

        if (inputFile.open(QIODevice::ReadOnly))
        {
           QTextStream in(&inputFile);

           for (int i = 0; !in.atEnd(); i++)
           {
              QString line = in.readLine();

              if(line == "")
                  break;

              split = line.split(",");
              ui->verticalLayout->addWidget(createCustGroup(split[0], split[2], split[3],split[4],split[5]));
           }

           inputFile.close();
        }
    }

    ui->verticalLayout->setAlignment(Qt::AlignCenter);

    QSpacerItem* space = new QSpacerItem(10, 10, QSizePolicy::Minimum, QSizePolicy::Expanding);
    ui->verticalLayout->addSpacerItem(space);
    spaces.push_back(space);
}

void show_accounts::on_pushButton_clicked()
{
    close();
}

void show_accounts::getUserName(QString str)
{
    type = str;
    show_list();
}

