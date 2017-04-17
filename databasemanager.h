#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QDialog>
#include <QTreeView>
#include <QMessageBox>
#include <QStandardItemModel>
#include <QItemSelectionModel>
#include <QCheckBox>
#include <boost/scoped_ptr.hpp>
#include <driver/mysql_public_iface.h>
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include "databasecontainer.h"
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
    void displayDatabases();
    ~DatabaseManager();
    void setMysqlUsername(QString username);
    void setMysqlPassword(QString password);
    void setMysqlHost(QString host);
    QString getMysqlUsername();
    QString getMysqlPassword();
    QString getMysqlHost();
    QStringList databaseList;

private:
    Ui::DatabaseManager *ui;
    QString msg;
    sql::Driver * driver;
    QStandardItemModel *standardModel;
    QStandardItem *rootNode;
    QStandardItemModel *standardModel2;
    QStandardItem *rootNode2;
    databasecontainer<QString> *container;
    node<QString> *head;
    QMessageBox *mysql_msg;
    QString mysql_host;
    QString mysql_password;
    QString mysql_username;

private slots:
    void connectToMysqlServer(QString host, QString username, QString password);
    void testConnection(QString host, QString username, QString password);
    void echo(const QModelIndex &index);
    void backupDatabases();

};


#endif // DATABASEMANAGER_H
