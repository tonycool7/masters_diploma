#ifndef POSTGRESQLDATABASEMANAGER_H
#define POSTGRESQLDATABASEMANAGER_H

#include "databasemanager.h"

class PostgreSQLDatabaseManager : public DatabaseManager
{
    Q_OBJECT

public:
    PostgreSQLDatabaseManager();
    ~PostgreSQLDatabaseManager();
    void executeBackup(int option, databasecontainer<QString> *selected);
    QString folderName();
    bool createPGPASSFile();

protected slots:
    void connectToServer(QString host_val, QString username_val, QString password_val);
    void testConnection(QString host_val, QString username_val, QString password_val);
    void backupDatabases();
    void storeInRemoteBackupFolder(bool value);
};

#endif // POSTGRESQLDATABASEMANAGER_H
