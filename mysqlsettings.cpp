#include "mysqlsettings.h"
#include "ui_mysqlsettings.h"

mysqlSettings::mysqlSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mysqlSettings)
{
    ui->setupUi(this);
    setFixedSize(841, 550);
    for(int i = 0; i < 4; i++){
        ui->mysql_timetable_tabwidget->setTabEnabled(i, false);
    }
    DatabaseManager *db = new MysqlDatabaseManager();

    connect(ui->loadDefualt, SIGNAL(clicked()), this, SLOT(loadMySQLDefault()));

    connect(ui->mysql_dynamic_naming, SIGNAL(toggled(bool)), ui->mysql_configuration_name, SLOT(setDisabled(bool)));

    connect(ui->mysql_cancel_btn, SIGNAL(clicked()), this, SLOT(close()));
    connect(this, SIGNAL(sendParameters(QString,QString,QString)), db, SLOT(connectToServer(QString ,QString ,QString )));

    connect(ui->mysql_test_connection_btn, SIGNAL(clicked()), this, SLOT(testingConnection()));
    connect(this, SIGNAL(testingParameters(QString,QString,QString)), db, SLOT(testConnection(QString ,QString ,QString )));

}

mysqlSettings::~mysqlSettings()
{
    delete ui;
}

void mysqlSettings::setHost(QString value)
{
    host = value;
}

void mysqlSettings::setUsername(QString value)
{
    username = value;
}

void mysqlSettings::setPassword(QString value)
{
    password = value;
}

void mysqlSettings::setPort(QString value)
{
    port = value;
}

QString mysqlSettings::getHost()
{
    return host;
}

QString mysqlSettings::getUsername()
{
    return username;
}

QString mysqlSettings::getPassword()
{
    return password;
}

QString mysqlSettings::getPort()
{
    return port;
}

void mysqlSettings::testingConnection()
{
    setHost(ui->mysql_host->text());
    setUsername(ui->mysql_username->text());
    setPassword(ui->mysql_password->text());
    emit testingParameters(getHost(), getUsername(), getPassword());
}


void mysqlSettings::enableRemoteAutomaticBackup(bool value)
{
    ui->mysql_timetable_tabwidget->setEnabled(value);
}

void mysqlSettings::loadMySQLDefault()
{
    ui->mysql_host->setText("192.168.1.224");
    ui->mysql_username->setText("root");
    ui->mysql_password->setText("dlords");
}

void mysqlSettings::enableRemoteManaulBackup(bool value)
{
    ui->mysql_destination_details->setEnabled(value);
    emit storeInMySQLRemoteBackupFolder(value);
}
