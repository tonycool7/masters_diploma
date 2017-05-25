#include "mysqldatabasemanager.h"

MysqlDatabaseManager::MysqlDatabaseManager()
{
    driver = sql::mysql::get_driver_instance();
}

MysqlDatabaseManager::~MysqlDatabaseManager()
{

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
        show();
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
