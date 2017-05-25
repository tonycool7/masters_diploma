#include "databasemanager.h"
#include "ui_databasemanager.h"

DatabaseManager::DatabaseManager(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DatabaseManager)
{
    ui->setupUi(this);
    StandardModel = new QStandardItemModel;
    StandardModel2 = new QStandardItemModel;
    msg = new QMessageBox(this);

    connect(ui->databaseView, SIGNAL(clicked(QModelIndex)), this, SLOT(displayDatabaseSelections(QModelIndex)));

    ui->databaseView->setModel(StandardModel);
    ui->seletedView->setModel(StandardModel2);

}

DatabaseManager::~DatabaseManager()
{
    delete ui;
}

void DatabaseManager::setUsername(QString username_val)
{
    username = username_val;
}

void DatabaseManager::setPassword(QString password_val)
{
    password = password_val;
}

void DatabaseManager::setHost(QString host_val)
{
    host = host_val;
}

QString DatabaseManager::getUsername()
{
    return username;
}

QString DatabaseManager::getPassword()
{
    return password;
}

QString DatabaseManager::getHost()
{
    return host;
}

void DatabaseManager::displayDatabases(node<QString> *head)
{
    if(!StandardModel->hasChildren()){
        StandardModel->setHorizontalHeaderItem(0, new QStandardItem("Database"));
        ContainerRootNode = StandardModel->invisibleRootItem();
        StandardModel2->setHorizontalHeaderItem(0, new QStandardItem("Selected"));
        ContainerRootNode2 = StandardModel2->invisibleRootItem();
        QVector<QString> tables;
        QStandardItem *mysql = new QStandardItem("Databases");
        ContainerRootNode->appendRow(mysql);

        while(head != NULL){
            QStandardItem *item = new QStandardItem(head->dbname);
            mysql->appendRow(item);
            item->setSelectable(true);
            item->setEditable(false);
            item->setCheckable(true);
            QVector<QString>::iterator it;
            for(it = head->tables.begin(); it != head->tables.end(); it++){
                QStandardItem *childItem = new QStandardItem(*it);
                childItem->setSelectable(true);
                childItem->setEditable(false);
                childItem->setCheckable(true);
                item->appendRow(childItem);
            }
            head = head->next;
        }
    }
}

void DatabaseManager::displayDatabaseSelections(const QModelIndex &index)
{
    QModelIndexList id = StandardModel2->match(StandardModel2->index(0, 0),Qt::DisplayRole,QVariant::fromValue(index.data()),2, Qt::MatchRecursive);
    QModelIndexList id2 = StandardModel2->match(StandardModel2->index(0, 0),Qt::DisplayRole,QVariant::fromValue(index.parent().data()),2, Qt::MatchRecursive);
    if(StandardModel->itemFromIndex(index)->checkState() == Qt::Checked && id.empty()){
        QStandardItem *selected = new QStandardItem(index.data().toString());
        if(index.parent().data() != "Databases"){
            if(!id2.empty()){
                ContainerRootNode2->child(id2.value(0).row(),0)->appendRow(selected);
            }else{
                StandardModel->itemFromIndex(index)->parent()->setCheckState(Qt::Checked);
                QStandardItem *selectedParent = new QStandardItem(index.parent().data().toString());
                ContainerRootNode2->appendRow(selectedParent);
                selectedParent->appendRow(selected);
            }
        }else{
             ContainerRootNode2->appendRow(selected);
        }
    }else{
        if(StandardModel->itemFromIndex(index)->checkState() == Qt::Unchecked){
            if(ContainerRootNode2->rowCount() == 0){
               ContainerRootNode2->removeRow(id.value(0).row());
            }else{
                if(!id2.empty()){
                    ContainerRootNode2->child(id2.value(0).row(),0)->removeRow(id.value(0).row());
                }else{
                    ContainerRootNode2->removeRow(id.value(0).row());
                }
            }
        }
    }

}

QString DatabaseManager::convertVectorToString(QVector<QString> data){
    QVector<QString>::iterator it;
    QString result = "";
    for(it = data.begin(); it != data.end(); it++){
        result += " "+(*it);
    }

    return result;
}

