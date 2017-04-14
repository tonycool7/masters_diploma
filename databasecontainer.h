#ifndef DATABASECONTAINER_H
#define DATABASECONTAINER_H

#include "node.h"
#include <QDebug>

template<typename containerType>
class databasecontainer
{
private:
    node<containerType>* root;

public:
    databasecontainer();
    ~databasecontainer(){}
    void populateDbContainer(containerType data, QVector<containerType> tables);
    node<containerType> *createNewNode(containerType data, QVector<containerType> table);
    node<containerType> *top();
    void displayDatabaseContainer();
    void searchAndSelect(QString &data);
};

template<typename containerType>
databasecontainer<containerType>::databasecontainer()
{
    root = NULL;
}

template<typename containerType>
void databasecontainer<containerType>::populateDbContainer(containerType data, QVector<containerType> tables)
{
    node<containerType> *temp = createNewNode(data, tables);
    if(root == NULL){
        root = temp;
    }else{
        node<containerType> *cur = root;
        while(cur->next != NULL){
            cur = cur->next;
        }
        cur->next = temp;
    }
}


template<typename containerType>
node<containerType> *databasecontainer<containerType>::createNewNode(containerType data, QVector<containerType> tables)
{
    node<containerType> *temp = new node<containerType>();
    temp->dbname = data;
    temp->tables = tables;
    temp->next = NULL;
    return temp;
}

template<typename containerType>
node<containerType> *databasecontainer<containerType>::top()
{
    return root;
}

template<typename containerType>
void databasecontainer<containerType>::displayDatabaseContainer()
{
    node<containerType> *temp;
    temp = top();

    while(temp != NULL){
        qDebug() << temp->dbname;
        QVector<QString>::iterator it;
        for(it = temp->tables.begin(); it != temp->tables.end(); it++){
            qDebug() <<"-"<< *it;
        }
        temp = temp->next;
    }
}


template<typename containerType>
void databasecontainer<containerType>::searchAndSelect(QString &data)
{
    node<containerType> *temp;
    temp = top();

    while(temp != NULL){
        qDebug() << temp->dbname;
        QVector<QString>::iterator it;
        for(it = temp->tables.begin(); it != temp->tables.end(); it++){
            qDebug() <<"-"<< *it;
        }
        temp = temp->next;
    }
}


#endif // DATABASECONTAINER_H
