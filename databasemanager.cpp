#include "databasemanager.h"
#include "ui_databasemanager.h"

DatabaseManager::DatabaseManager(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DatabaseManager)
{
    ui->setupUi(this);
    StandardModel = new QStandardItemModel;
    StandardModel2 = new QStandardItemModel;
    driver = sql::mysql::get_driver_instance();
    mysql_msg = new QMessageBox(this);

    connect(ui->databaseView, SIGNAL(clicked(QModelIndex)), this, SLOT(displayDatabaseSelections(QModelIndex)));
    connect(ui->backup_btn, SIGNAL(clicked()), this, SLOT(backupDatabases()));
    ui->databaseView->setModel(StandardModel);
    ui->seletedView->setModel(StandardModel2);

    mysql_remote_backup = false;
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

void DatabaseManager::testMysqlConnection(QString host, QString username, QString password)
{
    try{
        boost::scoped_ptr< sql::Connection > con(driver->connect(host.toStdString(), username.toStdString(), password.toStdString()));
            mysql_msg->information(this, tr("Testing connection to MySQL server"),tr("Connection to MySQL server was successful"), mysql_msg->Cancel, mysql_msg->Cancel);
    }catch(sql::SQLException &e){
            mysql_msg->critical(this, tr("Testing connection to MySQL server"),tr("Connection to MySQL Server unsuccessful "), mysql_msg->Cancel, mysql_msg->Cancel);
    }
}

void DatabaseManager::connectToPostgreSQLServer(QString host, QString username, QString password)
{
    setHost(host);
    setPassword(password);
    setUsername(username);
    try{
        pqxx::connection c{"host="+host.toStdString()+" dbname=postgres user="+username.toStdString()+" password="+password.toStdString()};
        pqxx::work txn{c};
        pqxx::result r = txn.exec("SELECT datname FROM pg_database WHERE datistemplate = false");
        PostgreSQLContainer = new databasecontainer<QString>();
        for (auto row: r){
            row[0].c_str();
            pqxx::connection c2{"host="+host.toStdString()+" dbname="+row[0].c_str()+" user="+username.toStdString()+" password="+password.toStdString()};
            pqxx::work txn{c2};
            pqxx::result r2 = txn.exec("SELECT * FROM information_schema.tables where table_schema='public'");
            QVector<QString> tables;
            for (auto row2: r2){
                tables << row2[2].c_str();
            }
            PostgreSQLContainer->populateDbContainer(row[0].c_str(), tables);
        }
        ui->label->setText("connection successfull!");
        containerHead = PostgreSQLContainer->top();
        displayDatabases(containerHead);
        show();
    }catch(const pqxx::sql_error &e){
        qDebug() << e.what();
        mysql_msg->critical(this, tr("PostgreSQL Connection"), tr("Unable to connect"), mysql_msg->Cancel, mysql_msg->Cancel);
    }
}

void DatabaseManager::testPostgreSQLConnection(QString host, QString username, QString password)
{
    try{
        pqxx::connection postgreSQLConnection{"host="+host.toStdString()+" dbname=test user="+username.toStdString()+" password="+password.toStdString()};
        mysql_msg->information(this, tr("Testing connection to postgreSQL server"),tr("Connection to PostgreSQL server was successful"), mysql_msg->Cancel, mysql_msg->Cancel);
    }catch(const pqxx::sql_error &e){
        mysql_msg->critical(this, tr("Testing connection to postgreSQL server"),tr("Connection to postgreSQL Server unsuccessful "), mysql_msg->Cancel, mysql_msg->Cancel);
    }
}

void DatabaseManager::connectToMysqlServer(QString host, QString username, QString password){
    setHost(host);
    setPassword(password);
    setUsername(username);
    try{
        boost::scoped_ptr< sql::Connection > con(driver->connect(host.toStdString(), username.toStdString(), password.toStdString()));
        boost::scoped_ptr< sql::Statement > stmt(con->createStatement());
        boost::scoped_ptr< sql::ResultSet > res(stmt->executeQuery("show databases"));
        mysqlContainer = new databasecontainer<QString>();
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
                    mysqlContainer->populateDbContainer(res->getString("Database").c_str(), tables);
                }
            }
            ui->label->setText("connection successfull!");
            containerHead = mysqlContainer->top();
            displayDatabases(containerHead);
        }
        show();
    }catch(sql::SQLException &e){
        qDebug() << "Error";
        mysql_msg->critical(this, tr("Mysql Connection"), tr("Unable to connect"), mysql_msg->Cancel, mysql_msg->Cancel);
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

QString DatabaseManager::folderName(){
    if(mysql_remote_backup){
        return "remote";
    }else{
        return "backup";
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

void DatabaseManager::executeBackup(int option, databasecontainer<QString> *selected){
    QString filename="createDump.sh";
    QFile file(filename);
    QProcess *createDump = new QProcess();
    switch(option){
    case 1:
        if(file.open(QIODevice::WriteOnly | QIODevice::Text)){
        QTextStream out(&file);
            out << "#!/bin/sh\n";
            out << "mysqldump -h"<<getHost()<<" -u"<<getUsername()<<" -p"<<getPassword()<<" --databases"+selected->returnOnlyDatabasesFromContainer()+ " > "<<folderName()<<"/dump_databases_"+QDate::currentDate().toString("MM_dd_yyyy")+".sql";
            file.close();
        }
        createDump->start("/bin/sh" , QStringList() <<"createDump.sh");
        createDump->waitForFinished();
        createDump->close();
        break;
    case 2:
    {
        node<QString> *temp;
        temp = selected->top();
        QString result = "";
        while(temp != NULL){
            if(!temp->tables.empty()){
                result += " "+temp->dbname;
                result += convertVectorToString(temp->tables);
                if(file.open(QIODevice::WriteOnly | QIODevice::Text)){
                QTextStream out(&file);
                    out << "#!/bin/sh\n";
                    out << "mysqldump -h"<<getHost()<<" -u"<<getUsername()<<" -p"<<getPassword()<<" --tables"+result+ " > "<<folderName()<<"/dump_"+temp->dbname+"_"+QDate::currentDate().toString("MM_dd_yyyy")+".sql";
                    file.close();
                }
            }
            createDump->start("/bin/sh" , QStringList() <<"createDump.sh");
            createDump->waitForFinished();
            createDump->close();
            temp = temp->next;
            result = "";
        }
    }
        break;
    default:
        qDebug() << "wrong option";
        break;
    }
}

void DatabaseManager::backupDatabases()
{
    databasecontainer<QString> *selected = new databasecontainer<QString>();
    if(!QDir(folderName()).exists()){
        QDir().mkdir(folderName());
    }
    QString databases;
    QModelIndex in = StandardModel->index(0,0);
    for(int i = 0; i < mysqlContainer->size; i++){
        QModelIndex n = StandardModel->index(i, 0, in);
        QVector<QString> tables;
        if(StandardModel->itemFromIndex(n)->checkState() == Qt::Checked){
            databases = StandardModel->data(n).toString();
            if(StandardModel->itemFromIndex(n)->hasChildren()){
                for(int j = 0; j < StandardModel->itemFromIndex(n)->rowCount(); j++){
                    QModelIndex n2 = StandardModel->index(j, 0, StandardModel->itemFromIndex(n)->index());
                    if(StandardModel->itemFromIndex(n2)->checkState() == Qt::Checked){
                        tables << StandardModel->data(n2).toString();
                    }
                }
            }
            selected->populateDbContainer(databases, tables);
        }
    }
    executeBackup(1, selected);
    executeBackup(2, selected);
    StandardModel->clear();
    StandardModel2->clear();
    this->close();
    mysql_msg->information(this, tr("Backup Alert"), tr("Backup was successfull!"),mysql_msg->Cancel, mysql_msg->Cancel);
}

void DatabaseManager::storeInMySQLRemoteBackupFolder(bool value)
{
    mysql_remote_backup = value;
}

void DatabaseManager::storeInPostgreSQLRemoteBackupFolder(bool value)
{
    postgreSQL_remote_backup = value;
}
