#include "cloths.h"
#include "Global.h"
cloths::cloths(int type, QString name, QString image_file, QString Seller_username, QString Brand_name, QString Color, int Weight, int Price, int Stock, QString gender)
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
    this->gender=gender;
    number_sold=0;
}

QString cloths::get_gender()
{
    return gender;
}

void cloths::set_gender(QString mat)
{
    gender=mat;
}

int cloths::getIndex_vector() const
{
    return index_vector;
}

void cloths::setIndex_vector(int newIndex_vector)
{
    index_vector = newIndex_vector;
}
