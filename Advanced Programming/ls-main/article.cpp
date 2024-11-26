#include "article.h"
#include "Global.h"
article::article(int type,QString name,QString image_file, QString Seller_username, QString Brand_name, QString Color, int Weight, int Price, int Stock )
{
    this->name=name;
    image_File=image_file;
    seller_username=Seller_username;
    brand_name=Brand_name;
    color=Color;
    weight=Weight;
    price=Price;
    stock=Stock;
    id=Global::get_number_of_article()+1;
    Global::setNumber_of_article(id);
    this->type=type;
}

void article::set(int type,QString name,QString image_file, QString Seller_username, QString Brand_name, QString Color, int Weight, int Price, int Stock , int Id , int Number_sold)
{
    this->name=name;
    image_File=image_file;
    seller_username=Seller_username;
    brand_name=Brand_name;
    color=Color;
    weight=Weight;
    price=Price;
    stock=Stock;
    id=Id;
    number_sold=Number_sold;
    this->type=type;
}

void article::set_stock(int x)
{
    stock=x;
}

void article::set_Price(int x)
{
    price=x;
}

void article::set_number_sold(int x)
{
    number_sold=x;
}

QString article::get_image_file()
{
    return image_File;
}

QString article::get_seller_username()
{
    return seller_username;
}

QString article::get_brand_name()
{
   return brand_name;
}

QString article::get_color()
{
    return color;
}

int article::get_weight()
{
    return weight;
}

int article::get_price()
{
    return price;
}

int article::get_stock()
{
    return stock;
}

int article::get_id()
{
    return id;
}

int article::get_number_sold()
{
    return number_sold;
}

int article::get_type()
{
    return type;
}

QString article::get_name()
{
    return name;
}

void article::setImage_File(const QString &newImage_File)
{
    image_File = newImage_File;
}

void article::setName(const QString &newName)
{
    name = newName;
}

void article::setSeller_username(const QString &newSeller_username)
{
    seller_username = newSeller_username;
}

void article::setBrand_name(const QString &newBrand_name)
{
    brand_name = newBrand_name;
}

void article::setColor(const QString &newColor)
{
    color = newColor;
}

int article::getIndex_vector() const
{
    return index_vector;
}

void article::setIndex_vector(int newIndex_vector)
{
    index_vector = newIndex_vector;
}
