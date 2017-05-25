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
#include <QDateTime>
#include <QDate>
#include "sshmanager.h"

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
    virtual QString folderName() = 0;
    virtual void executeBackup(int option, databasecontainer<QString> *selected) = 0;
    QString convertVectorToString(QVector<QString> data);

protected:
    Ui::DatabaseManager *ui;
    QStandardItemModel *StandardModel;
    QStandardItem *ContainerRootNode;
    QStandardItemModel *StandardModel2;
    QStandardItem *ContainerRootNode2;
    databasecontainer<QString> *dbContainer;
    node<QString> *containerHead;
    QMessageBox *msg;
    QString host;
    QString password;
    QString username;
    bool remote_backup;
    sshManager *ssh;

protected slots:
    virtual void connectToServer(QString host_val, QString username_val, QString password_val) = 0;
    virtual void testConnection(QString host_val, QString username_val, QString password_val) = 0;
    void displayDatabaseSelections(const QModelIndex &index);
    virtual void backupDatabases() = 0;
    virtual void storeInRemoteBackupFolder(bool value) = 0;

};


#endif // DATABASEMANAGER_H
