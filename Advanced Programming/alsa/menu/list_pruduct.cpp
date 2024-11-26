#include "list_pruduct.h"
#include <QLineEdit>
#include <QMessageBox>
#include <QFile>
#include "product_detail.h"
#include "report_page.h"
#include "buylist.h"
#include "advanced_search.h"
#include "edit_product.h"

int list_pruduct::number = 0;

QGroupBox* list_pruduct::createGroup(int index)
{
    setMaximumHeight(700);
    setFixedHeight(700);
    setMinimumHeight(700);

    QStringList split = lines[index].split(",");

    QGroupBox *groupBox = new QGroupBox(split[1]);
    groups.push_back(groupBox);

    QVBoxLayout* button_layout = new QVBoxLayout();
    vlayout.push_back(button_layout);

    QVBoxLayout* price_layout = new QVBoxLayout();
    vlayout.push_back(price_layout);

    QHBoxLayout* horisental_layout = new QHBoxLayout();
    hlayout.push_back(horisental_layout);

    QVBoxLayout* main_layout = new QVBoxLayout();
    vlayout.push_back(main_layout);

    QLabel* photo = new QLabel();
    QPixmap photo_source{".\\prudoct_picture\\" + QString::number(ids[index].toInt()) + ".png"};
    photo->setPixmap(photo_source.scaled(100,100));
    labels.push_back(photo);

    long long fprice = split[2].toLongLong() * (100 - split[5].toInt());

    QLineEdit* price = new QLineEdit(split[2]);
    price->setDisabled(true);
    lineedits.push_back(price);

    QLineEdit* finally_price = new QLineEdit(QString::number(fprice / 100));
    finally_price->setReadOnly(true);
    lineedits.push_back(finally_price);

    QLabel* discount = new QLabel(split[5]+"%");
    labels.push_back(discount);

    QLabel* seen = new QLabel(split[6]+" 👁‍🗨");
    seen->setAlignment(Qt::AlignRight);
    seen->setWhatsThis("تعداد بازدید");
    labels.push_back(discount);

    if(split[5] == "0")
    {
        discount->setVisible(false);
        price->setVisible(false);
    }

    QString id = split[11];

    price->setMaximumWidth(60);
    price->setFixedWidth(60);
    price->setAlignment(Qt::AlignCenter);

    finally_price->setMaximumWidth(60);
    finally_price->setFixedWidth(60);
    finally_price->setAlignment(Qt::AlignCenter);

    discount->setAlignment(Qt::AlignCenter);
    discount->setStyleSheet("QLabel { background-color : red; color : white; font-size:20px;}");

    creat_button_lay(button_layout,id);

    price_layout->addWidget(price);
    price_layout->addWidget(discount);
    price_layout->addWidget(finally_price);

    horisental_layout->addWidget(photo);
    horisental_layout->addLayout(price_layout);
    horisental_layout->addLayout(button_layout);

    main_layout->addLayout(horisental_layout);
    main_layout->addWidget(seen);

    main_layout->setSizeConstraint(QLayout::SetFixedSize);
    groupBox->setLayout(main_layout);

    return groupBox;
}

QGroupBox *list_pruduct::createEmptyGroup()
{
    QGroupBox *groupBox = new QGroupBox{" "};
    setMaximumHeight(700);
    setFixedHeight(700);
    setMinimumHeight(700);

    groups.push_back(groupBox);

    return groupBox;
}

void list_pruduct::show_list(int index)
{
    for(int i = 0; i < groups.length(); i++)
        delete groups[i];

    groups.clear();

    int count = (index - 1) * 12;

    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 3; j++)
        {
            if(count >= lines.length())
            {
                grid->addWidget(createEmptyGroup(), i, j);
                continue;
            }

            grid->addWidget(createGroup(count), i, j);
            count ++;
        }
}

void list_pruduct::read(QString cust_name, QString name, long long min, long long max, int count, QString color, QString info1, QString info2, QString categ)
{
    lines.clear();
    ids.clear();

    QFile inputFile("prudoct.txt");
    QStringList split;

    if (inputFile.open(QIODevice::ReadOnly))
    {
       QTextStream in(&inputFile);

       for (int i = 0; !in.atEnd(); i++)
       {
          QString line = in.readLine();
          split = line.split(",");

          if(cust_name != "admin" && cust_name != "client")
              if(cust_name != split[0])
                  continue;

          if(name != "All")
              if(!split[1].contains(name))
                   continue;

          if(split[2].toLongLong() < min || split[2].toLongLong() > max)
               continue;

          if(count != 2)
          {
              if(count)
                  if(split[2].toInt() == 0)
                      continue;

              if(count == 0)
                  if(split[2].toInt())
                      continue;
          }

          if(color != "All")
              if(color != split[4])
                  continue;

          if(info1 != "All")
              if(info1 != split[8])
                  continue;

          if(info2 != "All")
              if(info2 != split[9])
                  continue;

          if(categ != "A")
              if(categ != split[12])
                  continue;

          lines.push_back(line);
          ids.push_back(split[11]);
       }

       inputFile.close();
    }

    numbers->setText("from " + QString::number(((lines.length() - 1) / 12) + 1));
}

list_pruduct::list_pruduct(QWidget *parent) :
    QDialog(parent)
{
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

    setWindowTitle(tr("لیست محصولات"));

    grid = new QGridLayout{this};

    button_lay = new QHBoxLayout();
    search_lay = new QHBoxLayout();
    page_lay = new QHBoxLayout();

    back = new QPushButton{"بازگشت"};
    connect(back,&QPushButton::clicked,[this] { on_back_button(); });

    next = new QPushButton{"صفحه بعد"};
    connect(next,&QPushButton::clicked,[this] { on_next_button(); });

    privious = new QPushButton{"صفحه قبل"};
    connect(privious,&QPushButton::clicked,[this] { on_privious_button(); });

    buy_list = new QPushButton{"سبد خرید"};
    connect(buy_list,&QPushButton::clicked,[this] { on_buy_list_button(); });

    page_number = new QLineEdit{"1"};
    page_number->setAlignment(Qt::AlignLeft);
    page_number->setMaximumWidth(30);
    page_number->setFixedWidth(30);
    page_number->setReadOnly(1);

    search = new QLineEdit;
    search->setPlaceholderText("search");
    connect(search,SIGNAL(textChanged(const QString &)),this,SLOT(search_changed(QString)));
    search->setMaximumWidth(180);
    search->setFixedWidth(180);

    categorate = new QComboBox();
    categorate->addItem("All");
    categorate->addItem("laptops");
    categorate->addItem("phones");
    categorate->addItem("clothing");
    categorate->addItem("whaches");
    connect(categorate,SIGNAL(currentIndexChanged(int)),this,SLOT(combo_changed(int)));

    advance_search = new QPushButton{"جستجوی پیشرفته"};
    connect(advance_search,SIGNAL(clicked()),this,SLOT(on_advanced_search_clicked()));

    numbers = new QLabel;

//    search_lay->addWidget(categorate);
//    search_lay->addWidget(search);

//    space = new QSpacerItem(30, 0);
//    page_lay->addSpacerItem(space);
//    page_lay->addWidget(privious);
//    page_lay->addWidget(page_number);
//    page_lay->addWidget(numbers);
//    page_lay->addWidget(next);
//    page_lay->addSpacerItem(space);
//    setMaximumWidth(1001);

//    button_lay->addWidget(advance_search);
//    button_lay->addWidget(buy_list);
//    button_lay->addWidget(back);

//    grid->addLayout(search_lay, 4, 0, 1, 1);
//    grid->addLayout(page_lay, 4, 1, 1, 1);
//    grid->addLayout(button_lay, 4, 2, 1, 1);

    button_lay->addWidget(categorate);
    button_lay->addWidget(search);

    space = new QSpacerItem(50, 0);
    button_lay->addSpacerItem(space);
    button_lay->addWidget(privious);
    button_lay->addWidget(page_number);
    button_lay->addWidget(numbers);
    button_lay->addWidget(next);
    button_lay->addSpacerItem(space);

    button_lay->addWidget(advance_search);
    button_lay->addWidget(buy_list);
    button_lay->addWidget(back);

    grid->addLayout(button_lay, 4, 0, 1, 3);

    setLayout(grid);
}

void list_pruduct::on_buy_button(QString id)
{
    QFile inputFile("buylist.txt");
    QStringList split;

    if (inputFile.open(QIODevice::ReadOnly))
    {
       QTextStream in(&inputFile);

       for (int i = 0; !in.atEnd(); i++)
       {
          QString line = in.readLine();
          split = line.split(",");

          if(split[4] == id && split[1] == username)
          {
              QMessageBox::warning(this,"اخطار","این کالا قبلا به سبد خرید اضافه شده است!");
              return;
          }
       }

       inputFile.close();
    }

    QFile File("prudoct.txt");

    if (File.open(QIODevice::ReadOnly))
    {
       QTextStream in(&File);

       for (int i = 0; ; i++)
       {
          QString line = in.readLine();
          split = line.split(",");

          if(split[11] == id)
             break;
       }

       inputFile.close();
    }

    int fprice = split[2].toInt() * (100 - split[5].toInt());

    QFile file("buylist.txt");
    file.open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Append);

    QTextStream stream( &file );

    stream << split[0] << "," << username << "," << QString::number(fprice / 100) << ",1," << id << "\n";
    file.close();

    QMessageBox::information(this,"تایید","با موفقیت به سبد خرید اضافه شد!");
}

void list_pruduct::on_detail_button(QString id)
{
    Product_detail* temp = new Product_detail{this};
        connect(this, SIGNAL(sendPruductId(QString)), temp, SLOT(getPruductId(QString)));
        temp->show();

        emit sendPruductId(id);

        QVector<QString> lines;
        QFile inputFile("prudoct.txt");
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

              if(split[11] == id)
                  line = split[0] + "," + split[1] + "," + split[2] + "," + split[3] + "," +
                  split[4] + "," + split[5] + "," + QString::number(split[6].toInt()+1) + "," + split[7] + "," +
                  split[8] + "," + split[9] + "," + split[10] + "," + split[11] + "," + split[12];

              lines.push_back(line);
           }

           inputFile.close();
        }

        QFile file("prudoct.txt");
        file.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text);
        QTextStream stream( &file );
        for(int i = 0; i < lines.length(); i++)
            stream << lines.at(i) << "\n";

        file.close();
        lines.clear();
}

void list_pruduct::get_end(QString)
{
    read(type,"All",0,1000000000000,2,"All","All","All","A");
    show_list(1);
}

void list_pruduct::on_report_button(QString id)
{
    report_page* temp = new report_page{this};
    connect(this, SIGNAL(sendId(QString,QString)), temp, SLOT(getId(QString,QString)));
    temp->show();

    emit sendId(username,id);
}

void list_pruduct::on_remove_button(QString id)
{
    QMessageBox::StandardButton question;

    question = QMessageBox::question(this, "توجه", "آیا میخواهید این کالا را حذف کنید؟",
                                  QMessageBox::Yes|QMessageBox::No);

    if (question == QMessageBox::No)
        return;

    QVector<QString> lines;
    QFile inputFile("prudoct.txt");
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

          if(split[11] == id)
              continue;

          lines.push_back(line);
       }

       inputFile.close();
    }

    QFile file("prudoct.txt");
    file.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text);
    QTextStream stream( &file );
    for(int i = 0; i < lines.length(); i++)
        stream << lines.at(i) << "\n";

    file.close();
    lines.clear();

    QFile photo("./prudoct_picture/" + id + ".png");
    photo.remove();

    read(type,"All",0,1000000000000,2,"All","All","All","A");
    show_list(1);
}

void list_pruduct::on_edit_button(QString id)
{
    Edit_product* temp = new Edit_product{this};

    connect(this, SIGNAL(sendPruductId(QString)), temp, SLOT(getPruductId(QString)));
    connect(temp, SIGNAL(show_end(QString)), this, SLOT(get_end(QString)));

    temp->show();

    emit sendPruductId(id);
}

void list_pruduct::on_back_button()
{
    close();
}

void list_pruduct::on_next_button()
{
    if((((lines.length() - 1) / 12) + 1) == page_number->text().toInt())
    {
        QMessageBox::warning(this,"اخطار","صفحه بعد وجود ندارد");
        return;
    }

    page_number->setText(QString::number(page_number->text().toInt()+1));
    show_list(page_number->text().toInt());
}

void list_pruduct::on_privious_button()
{
    if(page_number->text().toInt() == 1)
    {
        QMessageBox::warning(this,"اخطار","صفحه قبل وجود ندارد");
        return;
    }

    page_number->setText(QString::number(page_number->text().toInt()-1));
    show_list(page_number->text().toInt());
}

void list_pruduct::getUserName(QString str)
{
    username = str;

    if(username == "admin")
        type = username;

    else
        type = "client";

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
            type = List[0];
            break;
        }
    }

    myfile.close();

    read(type,"All",0,1000000000000,2,"All","All","All","A");
    show_list(1);
}

void list_pruduct::on_buy_list_button()
{
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

           if(split[1] == username)
               count++;
        }
        inputFile.close();
    }

    if(count == 0)
    {
        QMessageBox::information(this,"اخطار","سبذ خرید خالی می باشد");
        return;
    }

    buylist* temp = new buylist;
    connect(this, SIGNAL(sendPruductId(QString)), temp, SLOT(getsId(QString)));
    temp->show();
    emit sendPruductId(username);
    close();
}

void list_pruduct::combo_changed(int index)
{
    QString cat = categorate->currentText()[0];
    read(type,"All",0,1000000000000,2,"All","All","All",cat);

    if(lines.length() == 0)
    {
        QMessageBox::warning(this,"اخطار","در این دسته بندی کالایی وجود ندارد");
        categorate->setCurrentIndex(comboindex);
        return;
    }

    comboindex = index;
    show_list(1);
    page_number->setText("1");
}

void list_pruduct::search_changed(QString str)
{
    QString cat = categorate->currentText()[0];
    read(type,str,0,1000000000000,2,"All","All","All",cat);

    if(lines.length() == 0)
    {
        QMessageBox::warning(this,"اخطار","چنین نامی وجود ندارد");
        search->setText("");
        return;
    }

    show_list(1);
}

void list_pruduct::on_advanced_search_clicked()
{
    advanced_search* temp = new advanced_search{this};
    temp->show();
    connect(temp,SIGNAL(send_data(QString, QString, QString, int, long long, long long, QString,QString)),this,SLOT(advanced_search_get(QString, QString, QString, int, long long, long long, QString,QString)));
}

void list_pruduct::advanced_search_get(QString cat, QString color, QString sor, int state, long long min, long long max, QString info1, QString info2)
{
    read(type,"All",min,max,state,color,info1,info2,cat);
    sort(sor);
    show_list(1);
}

void list_pruduct::sort(QString type)
{
    if(type == "none")
        return;

    for (int i = 0; i < lines.length(); i++){
        for (int j = i+1; j < lines.length(); j++)
        {
        QStringList split1 = lines[i].split(",");
        QStringList split = lines[j].split(",");

        if(type == "sell")
            if(split[7].toInt() >= split1[7].toInt())
                 lines.swapItemsAt(i,j);

        if(type == "dis")
            if(split[5].toInt() >= split1[5].toInt())
                 lines.swapItemsAt(i,j);

        if(type == "seen")
            if(split[6].toInt() >= split1[6].toInt())
                 lines.swapItemsAt(i,j);
        }
    }
}

void list_pruduct::creat_button_lay(QVBoxLayout *button_layout,QString id)
{
    detail = new QPushButton{"جزئیات محصول"};
    connect(detail,&QPushButton::clicked,[this, id] { on_detail_button(id); });
    buttons.push_back(detail);

    if(type == "client")
    {
        buy = new QPushButton{"افزودن به سبد خرید"};
        connect(buy,&QPushButton::clicked,[this, id] { on_buy_button(id); });
        buttons.push_back(buy);

        report = new QPushButton{"گزارش تخلف"};
        connect(report,&QPushButton::clicked,[this, id] { on_report_button(id); });
        buttons.push_back(report);

        button_layout->addWidget(buy);
        button_layout->addWidget(detail);
        button_layout->addWidget(report);
    }

    else
    {
        remove = new QPushButton{"حذف کالا"};
        connect(remove,&QPushButton::clicked,[this, id] { on_remove_button(id); });
        buttons.push_back(remove);

        edit = new QPushButton{"ویرایش کالا"};
        connect(edit,&QPushButton::clicked,[this, id] { on_edit_button(id); });
        buttons.push_back(edit);

        button_layout->addWidget(edit);
        button_layout->addWidget(detail);
        button_layout->addWidget(remove);
    }
}

int list_pruduct::countlines(QString fname)
{
    QFile file(fname);
    int line_count = 0;
    QString line[100];
    QTextStream in(&file);

    file.open(QIODevice::ReadWrite);

    while( !in.atEnd())
    {
        line[line_count]=in.readLine();
        line_count++;
    }

    file.close();
    return line_count;
}

list_pruduct::~list_pruduct()
{
    delete grid;
    delete back;
    delete next;
    delete privious;
    delete page_number;
    delete numbers;
    delete button_lay;
    delete advance_search;
    delete search;
    delete categorate;
    delete button_lay;
    delete search_lay;
    delete page_lay;
    delete space;

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

    for(int i = 0; i < groups.length(); i++)
        delete groups[i];

    groups.clear();
}
