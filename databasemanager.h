#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QDialog>
#include <QTreeView>
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

private slots:
    void connectToMysqlServer();
    void echo(const QModelIndex &index);

};

#endif // DATABASEMANAGER_H
