#ifndef MYSQLDATABASEMANAGER_H
#define MYSQLDATABASEMANAGER_H

#include "databasemanager.h"

class MysqlDatabaseManager : public DatabaseManager
{
    Q_OBJECT

public:
    MysqlDatabaseManager();
    ~MysqlDatabaseManager();
    sql::Driver * driver;

protected slots:
    void connectToServer(QString host_val, QString username_val, QString password_val);
    void testConnection(QString host_val, QString username_val, QString password_val);
};

#endif // MYSQLDATABASEMANAGER_H
