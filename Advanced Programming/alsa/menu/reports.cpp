#include "reports.h"
#include "ui_reports.h"
#include "product_detail.h"
#include <QFile>
#include <QMessageBox>

reports::reports(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::reports)
{
    ui->setupUi(this);
    setWindowTitle("بررسی گزارشات");
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    show_list();
}

reports::~reports()
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

    for(int i = 0; i < hlayout.length(); i++)
        delete hlayout[i];

    hlayout.clear();

    for(int i = 0; i < groups.length(); i++)
        delete groups[i];

    groups.clear();

    for(int i = 0; i < buttons.length(); i++)
        delete buttons[i];

    buttons.clear();
}

QGroupBox* reports::createGroup(QString name, QString _type, QString details, QString id)
{
    QGroupBox *groupBox = new QGroupBox;
    groups.push_back(groupBox);

    QHBoxLayout* main_layout = new QHBoxLayout();
    hlayout.push_back(main_layout);

    QLabel* reporter = new QLabel{"گزارش دهنده"};
    labels.push_back(reporter);

    QPushButton* accept = new QPushButton{"مسدود کردن فروشنده"};
    QPushButton* ignore = new QPushButton{"رد گزارش"};
    QPushButton* report_detail = new QPushButton{"جزئیات گزارش"};

    connect(accept,&QPushButton::clicked,[this, id] { on_accept_button(id); });
    connect(ignore,&QPushButton::clicked,[this, id] { on_ignore_button(id); });
    connect(report_detail,&QPushButton::clicked,[this, details] { on_detail_button(details); });

    buttons.push_back(ignore);
    buttons.push_back(accept);
    buttons.push_back(report_detail);

    QLineEdit* reporter_lineedit = new QLineEdit(name);
    reporter_lineedit->setReadOnly(true);
    reporter_lineedit->setMaximumWidth(65);
    reporter_lineedit->setFixedWidth(65);
    reporter_lineedit->setAlignment(Qt::AlignCenter);
    lineedits.push_back(reporter_lineedit);

    QSpacerItem* Space = new QSpacerItem(20, 0, QSizePolicy::Fixed, QSizePolicy::Fixed);

    main_layout->addWidget(reporter);
    main_layout->addWidget(reporter_lineedit);
    main_layout->addItem(Space);

    main_layout->addWidget(report_detail);
    main_layout->addWidget(accept);
    main_layout->addWidget(ignore);

    main_layout->setSizeConstraint(QLayout::SetFixedSize);

    groupBox->setLayout(main_layout);
    return groupBox;
}

void reports::show_list()
{
    QFile inputFile("report.txt");
    QStringList split;

    if (inputFile.open(QIODevice::ReadOnly))
    {
       QTextStream in(&inputFile);

       for (int i = 0; !in.atEnd(); i++)
       {
          QString line = in.readLine();

          if(line == "")
              break;

          liens.push_front(line);
       }

       inputFile.close();
    }

   for (int i = 0; i < liens.length(); i++)
   {
      QStringList split = liens[i].split(",");

      ui->verticalLayout->addWidget(createGroup(split[0], split[2], split[4],split[1]));
   }

    ui->verticalLayout->setAlignment(Qt::AlignCenter);

    QSpacerItem* space = new QSpacerItem(10, 10, QSizePolicy::Minimum, QSizePolicy::Expanding);
    ui->verticalLayout->addSpacerItem(space);
    spaces.push_back(space);
}

void reports::on_detail_button(QString details)
{
    QMessageBox::information(this,"جزیات گزارش",details);
}

void reports::on_accept_button(QString id)
{
    QVector<QString> lines;
    QFile inputFile("report.txt");
    QStringList split;
    QString line;

    if (inputFile.open(QIODevice::ReadOnly))
    {
       QTextStream in(&inputFile);

       for (int i = 0; ; i++)
       {
          line = in.readLine();
          split = line.split(",");

          if(line == "")
              break;

          if(split[1] == id)
          {
              continue;
          }

          lines.push_back(line);
       }

       inputFile.close();
    }

    QFile file("report.txt");
    file.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text);
    QTextStream stream( &file );

    for(int i = 0; i < lines.length(); i++)
        stream << lines.at(i) << "\n";

    file.close();
    lines.clear();

    Read_file();
    bool check = false;
    for (int i = 0 ; i <name.size() ; i++){
        if(name[i] == customer(id)){
            check = true;
            Block.replace(i,"block");
            break;
        }
    }
    if(check)
        Write_to_file();

    QMessageBox::information(this,"تایید","فروشنده با موفقیت مسدود شد");
    close();
}

void reports::on_ignore_button(QString id)
{
    QVector<QString> lines;
    QFile inputFile("report.txt");
    QStringList split;
    QString line;

    if (inputFile.open(QIODevice::ReadOnly))
    {
       QTextStream in(&inputFile);

       for (int i = 0; ; i++)
       {
          line = in.readLine();
          split = line.split(",");

          if(line == "")
              break;

          if(split[1] == id)
          {
              continue;
          }

          lines.push_back(line);
       }

       inputFile.close();
    }

    QFile file("report.txt");
    file.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text);
    QTextStream stream( &file );

    for(int i = 0; i < lines.length(); i++)
        stream << lines.at(i) << "\n";

    file.close();
    lines.clear();

    QMessageBox::information(this,"تایید","گزارش رد شد");
    close();
}

QString reports::customer(QString id)
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
              return split[0];
       }

       inputFile.close();
    }
}
