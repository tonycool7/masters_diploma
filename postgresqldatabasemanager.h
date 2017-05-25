#ifndef POSTGRESQLDATABASEMANAGER_H
#define POSTGRESQLDATABASEMANAGER_H

#include "databasemanager.h"

class PostgreSQLDatabaseManager : public DatabaseManager
{
    Q_OBJECT

public:
    PostgreSQLDatabaseManager();
    ~PostgreSQLDatabaseManager();
    bool createPGPASSFile();

protected slots:
    void connectToServer(QString host_val, QString username_val, QString password_val);
    void testConnection(QString host_val, QString username_val, QString password_val);
};

#endif // POSTGRESQLDATABASEMANAGER_H
