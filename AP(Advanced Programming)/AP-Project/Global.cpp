#include "Global.h"
#include "sporting_goods.h"
#include "cloths.h"
QVector <QPair<QPair<int , QString>, QPair<QString , QString>>> Global::vec_tran;
int Global::number_of_article=0;
bool Global::buy=0;
void Global::load()
{
    vec_person.clear();
    Global glob;
    std::fstream te("save.txt" , std::ios::app);
    te.close();
    std::fstream in("save.txt" , std::ios::in);
    if (!in)
        return;
    else
    {
        std::string x , y;
        std::string name, username, password, password2, phone, address, mail ,type , ban ,moneybags;
        while (getline(in, name) && getline(in, username) && getline(in, phone) && getline(in, address) && getline(in, password) && getline(in, mail), getline(in, ban) && getline(in, type) && getline(in , moneybags))
        {
            Person x;
            x.set( QString::fromStdString(name), QString::fromStdString(username), QString::fromStdString(phone), QString::fromStdString(address), QString::fromStdString(password),QString::fromStdString(mail),stoi(ban), stoi(type) , stoi(moneybags));
            glob.vec_person.push_back(x);
        }
    }
    in .close();
    if(glob.vec_person.size()==0)
    {
        std::string x = "Admin", y = "Admin@gmail.com";
        Person admin;
        admin.set(QString::fromStdString(x), QString::fromStdString(x), QString::fromStdString(x), QString::fromStdString(x), QString::fromStdString(x), QString::fromStdString(y), 0, 0);
        vec_person.push_back(admin);
        save();
    }
}

void Global::save()
{
    Global glob;
    std::fstream out("save.txt", std::ios::out);
    for (int i = 0; i < glob.vec_person.size(); i++)
    {
        out << glob.vec_person[i].get_name().toStdString() << "\n"
            << glob.vec_person[i].get_user_name().toStdString() << "\n"
            << glob.vec_person[i].get_phone_number().toStdString() << "\n"
            << glob.vec_person[i].get_address().toStdString() << "\n"
            << glob.vec_person[i].get_password().toStdString() << "\n"
            << glob.vec_person[i].get_Mail().toStdString() << "\n"
            << glob.vec_person[i].get_ban() << "\n"
            << glob.vec_person[i].get_type() << "\n"
            << glob.vec_person[i].get_moneybags()<<"\n";
    }
    out.close();
}

void Global::load_article()
{
    vec_article_cloths.clear();
    vec_article_sporting_goods.clear();
    std::fstream te("save_article_file.txt" , std::ios::app);
    te.close();
    std::fstream in("save_article_file.txt" , std::ios::in);
    std::string nc;
    if(getline(in , nc))
        number_of_article=stoi(nc);
    if (!in)
        return;
    else
    {
        std::string  type,name,image_file,Seller_username,Brand_name,Color,Weight,Price,Stock,id , number_sold;
        while (getline(in,type)&&getline(in , name)&&getline(in, image_file) && getline(in, Seller_username) && getline(in, Brand_name) && getline(in, Color) && getline(in, Weight) && getline(in, Price), getline(in,Stock) && getline(in, id) && getline(in , number_sold))
        {
            if (stoi(type)==1)
            {
                Sporting_goods x;
                std::string material;
                x.set(stoi(type),
                      QString::fromStdString(name),
                      QString::fromStdString(image_file),
                      QString::fromStdString(Seller_username),
                      QString::fromStdString(Brand_name),
                      QString::fromStdString(Color),
                      stoi(Weight),
                      stoi(Price),
                      stoi(Stock),
                      stoi(id),
                      stoi(number_sold));
                getline(in , material);
                x.set_material(QString::fromStdString(material));
                vec_article_sporting_goods.push_back(x);
            }
            else
            {
                cloths x;
                std::string gender;
                x.set(stoi(type),
                      QString::fromStdString(name),
                      QString::fromStdString(image_file),
                      QString::fromStdString(Seller_username),
                      QString::fromStdString(Brand_name),
                      QString::fromStdString(Color),
                      stoi(Weight),
                      stoi(Price),
                      stoi(Stock),
                      stoi(id),
                      stoi(number_sold));
                getline(in , gender);
                x.set_gender(QString::fromStdString(gender));
                vec_article_cloths.push_back(x);
            }
            number_of_article++;
        }
    }
    in .close();
}

void Global::save_article()
{
    std::fstream out("save_article_file.txt" , std::ios::out);
    out<<number_of_article<<"\n";
    for (int i=0;i<vec_article_cloths.size() ; i++)
    {
        out<<vec_article_cloths[i].get_type()<<"\n"
           <<vec_article_cloths[i].get_name().toStdString()<<"\n"
           <<vec_article_cloths[i].get_image_file().toStdString()<<"\n"
           <<vec_article_cloths[i].get_seller_username().toStdString()<<"\n"
           <<vec_article_cloths[i].get_brand_name().toStdString()<<"\n"
           <<vec_article_cloths[i].get_color().toStdString()<<"\n"
           <<vec_article_cloths[i].get_weight()<<"\n"
           <<vec_article_cloths[i].get_price()<<"\n"
           <<vec_article_cloths[i].get_stock()<<"\n"
           <<vec_article_cloths[i].get_id()<<"\n"
           <<vec_article_cloths[i].get_number_sold()<<"\n"
           <<vec_article_cloths[i].get_gender().toStdString()<<"\n";
    }
    for (int i=0;i<vec_article_sporting_goods.size() ; i++)
    {
        out<<vec_article_sporting_goods[i].get_type()<<"\n"
           <<vec_article_sporting_goods[i].get_name().toStdString()<<"\n"
           <<vec_article_sporting_goods[i].get_image_file().toStdString()<<"\n"
           <<vec_article_sporting_goods[i].get_seller_username().toStdString()<<"\n"
           <<vec_article_sporting_goods[i].get_brand_name().toStdString()<<"\n"
           <<vec_article_sporting_goods[i].get_color().toStdString()<<"\n"
           <<vec_article_sporting_goods[i].get_weight()<<"\n"
           <<vec_article_sporting_goods[i].get_price()<<"\n"
           <<vec_article_sporting_goods[i].get_stock()<<"\n"
           <<vec_article_sporting_goods[i].get_id()<<"\n"
           <<vec_article_sporting_goods[i].get_number_sold()<<"\n"
           <<vec_article_sporting_goods[i].get_material().toStdString()<<"\n";
    }

    out.close();
}

void Global::save_buyer()
{
    std::fstream out("save_buyer.txt" , std::ios::out);
    for (int i=0;i<vec_of_Buyer.size() ; i++)
    {
        out<<vec_of_Buyer[i].first<<"\n"
           <<vec_of_Buyer[i].second.first.first<<"\n"
          <<vec_of_Buyer[i].second.first.second.toStdString()<<"\n"
         <<vec_of_Buyer[i].second.second.first.toStdString()<<"\n"
        <<vec_of_Buyer[i].second.second.second<<"\n";

    }
    out.close();
}

void Global::load_buyer()
{
    vec_of_Buyer.clear();
    std::fstream te("save_buyer.txt" , std::ios::app);
    te.close();
    std::fstream in("save_buyer.txt" , std::ios::in);
    if (!in)
        return;
    else
    {
        std::string number,name , id , date , price;
        while (getline(in,number),getline(in , id) && getline(in  , name) && getline(in , date) && getline(in, price))
        {
            vec_of_Buyer.push_back(qMakePair(stoi(number),qMakePair(qMakePair(stoi(id) , QString::fromStdString(name)) , qMakePair(QString::fromStdString(date) , stoi(price)))));
        }
    }
    in .close();
}

void Global::save_vec_tran()
{
    std::fstream out("save_tran.txt" , std::ios::out);
    for (int i=0;i<vec_tran.size() ; i++)
    {
        out<<vec_tran[i].first.first<<"\n"
          <<vec_tran[i].first.second.toStdString()<<"\n"
         <<vec_tran[i].second.first.toStdString()<<"\n"
        <<vec_tran[i].second.second.toStdString()<<"\n";

    }
    out.close();

}

void Global::load_tran()
{
    vec_tran.clear();
    std::fstream te("save_tran.txt" , std::ios::app);
    te.close();
    std::fstream in("save_tran.txt" , std::ios::in);
    if (!in)
        return;
    else
    {
        std::string number,name , id , date , price;
        while (getline(in,number),getline(in , id) && getline(in  , name) && getline(in , date))
        {
            vec_tran.push_back(qMakePair(qMakePair(stoi(number),QString::fromStdString(id)),qMakePair(QString::fromStdString(name),QString::fromStdString(date))));
        }
    }
    in .close();
}

int Global::serch_id_cloths(int id)
{
    for(int i=0;i<vec_article_cloths.size();i++)
        if (vec_article_cloths[i].get_id()==id)
               return i;
    return -1;
}

int Global::serch_id_sporting_goods(int id)
{
    for(int i=0;i<vec_article_sporting_goods.size();i++)
        if (vec_article_sporting_goods[i].get_id()==id)
               return i;
    return -1;
}

void Global::load_all()
{
    Global::load();
    Global::load_article();
    Global::load_buyer();
    Global::load_tran();
}

void Global::save_all()
{
    Global::save();
    Global::save_article();
    Global::save_buyer();
    Global::save_vec_tran();
}


int Global::get_number_of_article()
{
    return number_of_article;
}

void Global::setNumber_of_article(int newNumber_of_article)
{
    number_of_article = newNumber_of_article;
}

int Global::getIndex_vector() const
{
    return index_vector;
}

void Global::setIndex_vector(int newIndex_vector)
{
    index_vector = newIndex_vector;
}
