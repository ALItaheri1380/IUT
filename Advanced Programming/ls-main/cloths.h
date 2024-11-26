#ifndef CLOTHS_H
#define CLOTHS_H
#include "article.h"

class cloths:public article
{
public:
    cloths(){}
    cloths(int type,QString name,QString image_file , QString Seller_username , QString Brand_name  , QString Color , int Weight , int Price , int Stock ,QString gender );
    QString get_gender();
    void set_gender(QString mat);
    int getIndex_vector() const;
    void setIndex_vector(int newIndex_vector);

private:
    QString gender;
    int index_vector;
};

#endif // CLOTHS_H
