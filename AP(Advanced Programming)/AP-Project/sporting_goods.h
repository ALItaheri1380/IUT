#ifndef SPORTING_GOODS_H
#define SPORTING_GOODS_H
#include "article.h"
class Sporting_goods:public article
{
public:
    Sporting_goods(){};
    Sporting_goods(int type,QString name,QString image_file , QString Seller_username , QString Brand_name  , QString Color , int Weight , int Price , int Stock ,QString material );
    QString get_material();
    void set_material(QString mat);
    int getIndex_vector() const;
    void setIndex_vector(int newIndex_vector);

private:
    QString material;
    int index_vector;
};

#endif // SPORTING_GOODS_H
