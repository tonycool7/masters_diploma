#include "postgresqldatabasemanager.h"

PostgreSQLDatabaseManager::PostgreSQLDatabaseManager()
{

}

PostgreSQLDatabaseManager::~PostgreSQLDatabaseManager()
{

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

