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
    void setUsername(QString username);
    void setPassword(QString password);
    void setHost(QString host);
    QString getUsername();
    QString getPassword();
    QString getHost();
    QStringList databaseList;

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

private slots:
    void connectToMysqlServer(QString host, QString username, QString password);
    void testMysqlConnection(QString host, QString username, QString password);
    void connectToPostgreSQLServer(QString host, QString username, QString password);
    void testPostgreSQLConnection(QString host, QString username, QString password);
    void displayMysqlDatabaseSelections(const QModelIndex &index);
    void backupDatabases();

};


#endif // DATABASEMANAGER_H
