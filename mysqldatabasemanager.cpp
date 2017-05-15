#include "mysqldatabasemanager.h"

MysqlDatabaseManager::MysqlDatabaseManager()
{

}

MysqlDatabaseManager::~MysqlDatabaseManager()
{

}

void MysqlDatabaseManager::executeBackup(int option, databasecontainer<QString> *selected)
{
    QString filename="createDump.sh";
    QFile file(filename);
    QProcess *createDump = new QProcess();
    switch(option){
    case 1:
        if(file.open(QIODevice::WriteOnly | QIODevice::Text)){
        QTextStream out(&file);
            out << "#!/bin/sh\n";
            out << "mysqldump -h"<<getHost()<<" -u"<<getUsername()<<" -p"<<getPassword()<<" --databases"+selected->returnOnlyDatabasesFromContainer()+ " > "<<folderName()<<"/dump_databases_"+QDate::currentDate().toString("MM_dd_yyyy")+"+"+QDateTime::currentDateTime().toString("hh:mm:ss")+".sql";
            file.close();
        }
        createDump->start("/bin/sh" , QStringList() <<"createDump.sh");
        createDump->waitForFinished(50000);
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
                    out << "mysqldump -h"<<getHost()<<" -u"<<getUsername()<<" -p"<<getPassword()<<" --tables"+result+ " > "<<folderName()<<"/dump_"+temp->dbname+"_"+QDate::currentDate().toString("MM_dd_yyyy")+"+"+QDateTime::currentDateTime().toString("hh:mm:ss")+".sql";
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

QString MysqlDatabaseManager::folderName()
{
    if(remote_backup){
        return "mySQLRemote";
    }else{
        return "mySQLBackup";
    }
}

void MysqlDatabaseManager::connectToServer(QString host_val, QString username_val, QString password_val)
{
    setHost(host_val);
    setPassword(password_val);
    setUsername(username_val);
    try{
        boost::scoped_ptr< sql::Connection > con(driver->connect(host.toStdString(), username.toStdString(), password.toStdString()));
        boost::scoped_ptr< sql::Statement > stmt(con->createStatement());
        boost::scoped_ptr< sql::ResultSet > res(stmt->executeQuery("show databases"));
        dbContainer = new databasecontainer<QString>();
        if (res->rowsCount() == 0) {
//            ui->label->setText("not connected!");
        }else{
            while (res->next()) {
                if(res->getString("Database").asStdString() != "information_schema" && res->getString("Database").asStdString() != "performance_schema"){
                    stmt->execute("USE "+ res->getString("Database").asStdString());
                    boost::scoped_ptr< sql::ResultSet > res2(stmt->executeQuery("show tables"));
                    if (res2->rowsCount() > 0) {
                        QVector<QString> tables;
                        while(res2->next()){
                            tables <<  res2->getString("Tables_in_"+res->getString("Database").asStdString()).c_str();
                        }
                        dbContainer->populateDbContainer(res->getString("Database").c_str(), tables);
                    }
                }
            }
            containerHead = dbContainer->top();
            displayDatabases(containerHead);
        }
        if(remote_backup){
            if(ssh->testSSHConnection(ssh->getSSHHost(), ssh->getSSHUsername(), ssh->getSSPassword())){
                show();
            }
        }else{
            show();
        }
    }catch(sql::SQLException &e){
        qDebug() << "Error";
        msg->critical(this, tr("Mysql Connection"), tr("Unable to connect"), msg->Cancel, msg->Cancel);
    }

}

void MysqlDatabaseManager::testConnection(QString host_val, QString username_val, QString password_val)
{
    setHost(host_val);
    setPassword(password_val);
    setUsername(username_val);
    try{
        boost::scoped_ptr< sql::Connection > con(driver->connect(host.toStdString(), username.toStdString(), password.toStdString()));
            msg->information(this, tr("Testing connection to MySQL server"),tr("Connection to MySQL server was successful"), msg->Ok, msg->Ok);
    }catch(sql::SQLException &e){
            msg->critical(this, tr("Testing connection to MySQL server"),tr("Connection to MySQL Server unsuccessful "), msg->Ok, msg->Ok);
    }
}

void MysqlDatabaseManager::storeInRemoteBackupFolder(bool value)
{
    remote_backup = value;
}

void MysqlDatabaseManager::backupDatabases()
{
    databasecontainer<QString> *selected = new databasecontainer<QString>();
    if(!QDir(folderName()).exists()){
        QDir().mkdir(folderName());
    }

    if(!QDir(folderName()).exists()){
        QDir().mkdir(folderName());
    }

    QString databases;
    QModelIndex in = StandardModel->index(0,0);
    for(int i = 0; i < dbContainer->size; i++){
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

    if(remote_backup){
        ssh->sendBackupToRemoteSSHServer(ssh->getSSHHost(), ssh->getSSHUsername(), ssh->getSSPassword());
    }
    this->close();
    msg->information(this, tr("Backup Alert"), tr("Backup was successfull!"),msg->Ok, msg->Ok);
}
