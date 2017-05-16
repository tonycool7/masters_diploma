#include "postgresqldatabasemanager.h"

PostgreSQLDatabaseManager::PostgreSQLDatabaseManager()
{
    ssh = sshManager::getSSHManager();
}

PostgreSQLDatabaseManager::~PostgreSQLDatabaseManager()
{

}

void PostgreSQLDatabaseManager::executeBackup(int option, databasecontainer<QString> *selected)
{
    QString filename="createPostgreSQLDump.sh";
    QFile file(filename);
    QProcess *createDump = new QProcess();
    switch(option){
    case 1:
    {
        QVector<QString>::iterator it;
        QVector<QString> db;
        db = selected->returnOnlyDatabasesFromContainerVector();

        for(it = db .begin(); it!=db.end(); ++it){
            if(file.open(QIODevice::WriteOnly | QIODevice::Text)){
            QTextStream out(&file);
                out << "#!/bin/sh\n";
                out << "pg_dump -w -U"<<getUsername()<<" "+(*it)<< " -f "<<folderName()<<"/dump_"+(*it)+"_"+QDate::currentDate().toString("MM_dd_yyyy")+"+"+QDateTime::currentDateTime().toString("hh:mm:ss")+".sql";
                file.close();
            }
            createDump->start("/bin/sh" , QStringList() <<"createPostgreSQLDump.sh");
            createDump->waitForFinished(50000);
            createDump->close();
        }
    }
        break;
    default:
        qDebug() << "wrong option";
        break;
    }
}

QString PostgreSQLDatabaseManager::folderName()
{
    if(remote_backup){
        return "postgreSQLRemote";
    }else{
        return "postgreSQLBackup";
    }
}

bool PostgreSQLDatabaseManager::createPGPASSFile()
{
    QString filename="~/.pgpass";
    QFile file(filename);
    QFile file2("changeMode.sh");
    QProcess *changeMod = new QProcess;
    if(file.open(QIODevice::WriteOnly | QIODevice::Text)){
        QTextStream out(&file);
        out << "*:*:*:*:"+getPassword();
        file.close();
    }

    if(file2.open(QIODevice::WriteOnly | QIODevice::Text)){
        QTextStream out(&file2);
        out << "chmod 600 ~/.pgpass";
        file2.close();
    }

    changeMod->execute("/bin/sh", QStringList() << "changeMode.sh");
    changeMod->waitForFinished();
    changeMod->close();

    return file.exists("/home/tony/.pgpass") ? true : false;
}

void PostgreSQLDatabaseManager::connectToServer(QString host_val, QString username_val, QString password_val)
{
    setHost(host_val);
    setPassword(password_val);
    setUsername(username_val);
    try{
        pqxx::connection c{"host="+host.toStdString()+" dbname=postgres user="+username.toStdString()+" password="+password.toStdString()};
        pqxx::work txn{c};
        pqxx::result r = txn.exec("SELECT datname FROM pg_database WHERE datistemplate = false");
        dbContainer = new databasecontainer<QString>();
        for (auto row: r){
            row[0].c_str();
            pqxx::connection c2{"host="+host.toStdString()+" dbname="+row[0].c_str()+" user="+username.toStdString()+" password="+password.toStdString()};
            pqxx::work txn{c2};
            pqxx::result r2 = txn.exec("SELECT * FROM information_schema.tables where table_schema='public'");
            QVector<QString> tables;
            for (auto row2: r2){
                tables << row2[2].c_str();
            }
            dbContainer->populateDbContainer(row[0].c_str(), tables);
        }

        if(createPGPASSFile()){
            containerHead = dbContainer->top();
            displayDatabases(containerHead);
            if(remote_backup){
                ssh->testSSHConnection(ssh->getSSHHost(), ssh->getSSHUsername(), ssh->getSSPassword());
            }
            show();
        }else{
            QMessageBox::critical(this, tr("PostgresQL Error"), tr("Unable to create file '~/.pgpass'"), QMessageBox::Ok, QMessageBox::Ok);
        }



    }catch(const pqxx::sql_error &e){
        qDebug() << e.what();
        msg->critical(this, tr("PostgreSQL Connection"), tr("Unable to connect"), msg->Ok, msg->Ok);
    }
}

void PostgreSQLDatabaseManager::testConnection(QString host_val, QString username_val, QString password_val)
{
    setHost(host_val);
    setPassword(password_val);
    setUsername(username_val);
    try{
        pqxx::connection postgreSQLConnection{"host="+host.toStdString()+" dbname=test user="+username.toStdString()+" password="+password.toStdString()};
        msg->information(this, tr("Testing connection to postgreSQL server"),tr("Connection to PostgreSQL server was successful"), msg->Ok, msg->Ok);
    }catch(const pqxx::sql_error &e){
        msg->critical(this, tr("Testing connection to postgreSQL server"),tr("Connection to postgreSQL Server unsuccessful "), msg->Ok, msg->Ok);
    }
}

void PostgreSQLDatabaseManager::backupDatabases()
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

    if(remote_backup){
        ssh->sendBackupToRemoteSSHServer(ssh->getSSHHost(), ssh->getSSHUsername(), ssh->getSSPassword(), folderName());
    }
    this->close();
    msg->information(this, tr("Backup Alert"), tr("Backup was successfull!"),msg->Ok, msg->Ok);
}

void PostgreSQLDatabaseManager::storeInRemoteBackupFolder(bool value)
{
    remote_backup = value;
}
