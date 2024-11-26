#ifndef GLOBAL_H
#define GLOBAL_H
#include "QVector"
#include "Person.h"
#include "article.h"
#include "fstream"
#include <QFileDialog>
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <iostream>
#include <QString>
#include "sporting_goods.h"
#include "cloths.h"
class Global{
public:
    static QVector <Person> vec_person;
    static Person Active_person[20];
    static QVector<cloths> vec_article_cloths;
    static QVector<Sporting_goods> vec_article_sporting_goods;
    static QVector <QPair<int,QPair<QPair<int,QString> , QPair<QString , int>>>> vec_of_Buyer;// number id usernaem date  price
    static QVector <QPair<QPair<int , QString>, QPair<QString , QString>>> vec_tran;
    static QVector<QPair<int , int > > Shopping_cart[20];
    static void load();
    static void save();
    static void load_article();
    static void save_article();
    static void save_buyer();
    static void load_buyer();
    static void save_vec_tran();
    static void load_tran();
    static int serch_id_cloths(int id);
    static int serch_id_sporting_goods(int id);
    static bool buy;
    static void load_all();
    static void save_all();

    static int get_number_of_article();

    static void setNumber_of_article(int newNumber_of_article);

    int getIndex_vector() const;
    void setIndex_vector(int newIndex_vector);
private:
    static int number_of_article;
    int index_vector{0};

};
#endif // GLOBAL_H
