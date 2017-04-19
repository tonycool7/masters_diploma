#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QDialog>
#include <iostream>
#include <QTreeView>
#include <QMessageBox>
#include <QStandardItemModel>
#include <QItemSelectionModel>
#include <QCheckBox>
#include <boost/scoped_ptr.hpp>
#include <driver/mysql_public_iface.h>
#include <mysql_connection.h>
#include <stdlib.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include "databasecontainer.h"
#include <signal.h>
#include <pqxx/pqxx>
#include <QFile>
#include <QProcess>
#include <QTextStream>
#include <QDir>
#include <QDate>

using namespace std;

namespace Ui {
    class DatabaseManager;
}

class DatabaseManager : public QDialog
{
    Q_OBJECT

public:
    explicit DatabaseManager(QWidget *parent = 0);
    void displayDatabases(node<QString> *head);
    ~DatabaseManager();
    void setUsername(QString username_val);
    void setPassword(QString password_val);
    void setHost(QString host_val);
    QString getUsername();
    QString getPassword();
    QString getHost();
    QStringList databaseList;
    QString folderName();
    void executeBackup(int option, databasecontainer<QString> *selected);
    QString convertVectorToString(QVector<QString> data);

private:
    Ui::DatabaseManager *ui;
    QString msg;
    sql::Driver * driver;
    QStandardItemModel *StandardModel;
    QStandardItem *ContainerRootNode;
    QStandardItemModel *StandardModel2;
    QStandardItem *ContainerRootNode2;
    databasecontainer<QString> *mysqlContainer;
    databasecontainer<QString> *PostgreSQLContainer;
    node<QString> *containerHead;
    QMessageBox *mysql_msg;
    QString host;
    QString password;
    QString username;
    bool mysql_remote_backup;
    bool postgreSQL_remote_backup;

private slots:
    void connectToMysqlServer(QString host_val, QString username_val, QString password_val);
    void testMysqlConnection(QString host_val, QString username_val, QString password_val);
    void connectToPostgreSQLServer(QString host_val, QString username_val, QString password_val);
    void testPostgreSQLConnection(QString host_val, QString username_val, QString password_val);
    void displayDatabaseSelections(const QModelIndex &index);
    void backupDatabases();
    void storeInMySQLRemoteBackupFolder(bool value);
    void storeInPostgreSQLRemoteBackupFolder(bool value);

};


#endif // DATABASEMANAGER_H
