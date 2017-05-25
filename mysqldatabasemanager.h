#ifndef MYSQLDATABASEMANAGER_H
#define MYSQLDATABASEMANAGER_H

#include "databasemanager.h"

class MysqlDatabaseManager : public DatabaseManager
{
    Q_OBJECT

public:
    MysqlDatabaseManager();
    ~MysqlDatabaseManager();
    QString mySQLFolderName();
    void executeBackup(int option, databasecontainer<QString> *selected);
    QString folderName();
    sql::Driver * driver;

protected slots:
    void connectToServer(QString host_val, QString username_val, QString password_val);
    void testConnection(QString host_val, QString username_val, QString password_val);
    void storeInRemoteBackupFolder(bool value);
    void backupDatabases();
};

#endif // MYSQLDATABASEMANAGER_H
