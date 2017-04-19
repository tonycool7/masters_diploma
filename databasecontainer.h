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
    bool searchForDb(QString data);
    QString returnOnlyDatabasesFromContainer();
    int size;
};

template<typename containerType>
databasecontainer<containerType>::databasecontainer()
{
    root = NULL;
}


template<typename containerType>
QString databasecontainer<containerType>::returnOnlyDatabasesFromContainer(){
    node<containerType> *temp;
    temp = top();

    QString result = "";
    while(temp != NULL){
        if(temp->tables.empty()){
            result += " "+temp->dbname;
        }
        temp = temp->next;
    }
    return result;
}


template<typename containerType>
void databasecontainer<containerType>::populateDbContainer(containerType data, QVector<containerType> tables)
{
    node<containerType> *temp = createNewNode(data, tables);
    if(root == NULL){
        root = temp;
        size = 0;
    }else{
        node<containerType> *cur = root;
        while(cur->next != NULL){
            cur = cur->next;
        }
        cur->next = temp;
    }

    size++;
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
bool databasecontainer<containerType>::searchForDb(QString data)
{
    node<containerType> *temp;
    temp = top();

    while(temp != NULL){
        if(temp->dbname == data){
            return true;
        }
        temp = temp->next;
    }

    return false;
}


#endif // DATABASECONTAINER_H
