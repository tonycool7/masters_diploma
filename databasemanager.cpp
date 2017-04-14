#include "databasemanager.h"
#include "ui_databasemanager.h"

DatabaseManager::DatabaseManager(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DatabaseManager)
{
    ui->setupUi(this);
    standardModel = new QStandardItemModel ;
    standardModel->setHorizontalHeaderItem(0, new QStandardItem("Database"));
    rootNode = standardModel->invisibleRootItem();

    standardModel2 = new QStandardItemModel ;
    standardModel2->setHorizontalHeaderItem(0, new QStandardItem("Selected"));
    rootNode2 = standardModel2->invisibleRootItem();
    driver = sql::mysql::get_driver_instance();

    connect(ui->databaseView, SIGNAL(clicked(QModelIndex)), this, SLOT(echo(QModelIndex)));
    ui->databaseView->setModel(standardModel);
    ui->seletedView->setModel(standardModel2);
}

DatabaseManager::~DatabaseManager()
{
    delete ui;
}

void DatabaseManager::displayDatabases()
{
    QVector<QString> tables;
    head = container->top();
    QStandardItem *mysql = new QStandardItem("MySQL Databases");
    rootNode->appendRow(mysql);
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

void DatabaseManager::connectToMysqlServer(){
    try{
        boost::scoped_ptr< sql::Connection > con(driver->connect("localhost", "root", "dlords"));
        boost::scoped_ptr< sql::Statement > stmt(con->createStatement());
        boost::scoped_ptr< sql::ResultSet > res(stmt->executeQuery("show databases"));
        container = new databasecontainer<QString>();
        if (res->rowsCount() == 0) {
            ui->label->setText("not connected!");
        }else{
            while (res->next()) {
                stmt->execute("USE "+ res->getString("Database").asStdString());
                boost::scoped_ptr< sql::ResultSet > res2(stmt->executeQuery("show tables"));
                if (res2->rowsCount() > 0) {
                    QVector<QString> tables;
                    while(res2->next()){
                        tables <<  res2->getString("Tables_in_"+res->getString("Database").asStdString()).c_str();
                    }
                    container->populateDbContainer(res->getString("Database").c_str(), tables);
                }
            }
            ui->label->setText("connection successfull!");
            displayDatabases();
        }
    }catch(sql::SQLException &e){
        qDebug() << "Error";
    }
}

void DatabaseManager::echo(const QModelIndex &index)
{
    QModelIndexList id = standardModel2->match(standardModel2->index(0, 0),Qt::DisplayRole,QVariant::fromValue(index.data()),2, Qt::MatchRecursive);

    if(standardModel->itemFromIndex(index)->checkState() == Qt::Checked && id.empty()){
        QStandardItem *selected = new QStandardItem(index.data().toString());
        if(index.parent().data() != "MySQL Databases"){
            QModelIndexList id2 = standardModel2->match(standardModel2->index(0, 0),Qt::DisplayRole,QVariant::fromValue(index.parent().data()),2, Qt::MatchRecursive);
            if(!id2.empty()){
                rootNode2->child(id2.value(0).row(),0)->appendRow(selected);
            }else{
                QStandardItem *selectedParent = new QStandardItem(index.parent().data().toString());
                rootNode2->appendRow(selectedParent);
                selectedParent->appendRow(selected);
            }
        }else{
             rootNode2->appendRow(selected);
        }
    }else{
        if(standardModel->itemFromIndex(index)->checkState() == Qt::Unchecked){
            rootNode2->removeRow(id.value(0).row());
        }
    }

}

