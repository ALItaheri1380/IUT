#include "sporting_goods.h"
#include "Global.h"
Sporting_goods::Sporting_goods(int type, QString name, QString image_file, QString Seller_username, QString Brand_name, QString Color, int Weight, int Price, int Stock, QString material)
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
    this->material=material;
    number_sold=0;
}

QString Sporting_goods::get_material()
{
    return material;
}

void Sporting_goods::set_material(QString mat)
{
    material=mat;
}

int Sporting_goods::getIndex_vector() const
{
    return index_vector;
}

void Sporting_goods::setIndex_vector(int newIndex_vector)
{
    index_vector = newIndex_vector;
}

