#ifndef NODE_H
#define NODE_H


#include <QVector>

template<typename database>
class node{
public:
    database dbname;
    QVector<database> tables;
    node *next;
    bool selected;

    node(){next = NULL;}
    ~node();
};

#endif // NODE_H
