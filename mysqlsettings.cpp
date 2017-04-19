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
    DatabaseManager *db = new DatabaseManager();
    ssh = new sshManager();

    connect(ui->loadDefualt, SIGNAL(clicked()), this, SLOT(loadDefault()));

    connect(this, SIGNAL(storeInMySQLRemoteBackupFolder(bool)), db, SLOT(storeInMySQLRemoteBackupFolder(bool)));

    connect(ui->mysql_dynamic_naming, SIGNAL(toggled(bool)), ui->mysql_configuration_name, SLOT(setDisabled(bool)));

    connect(ui->mysql_cancel_btn, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->mysql_ok_btn, SIGNAL(clicked()), this, SLOT(tryingToConnect()));
    connect(this, SIGNAL(sendParameters(QString,QString,QString)), db, SLOT(connectToMysqlServer(QString ,QString ,QString )));

    connect(ui->mysql_test_connection_btn, SIGNAL(clicked()), this, SLOT(testingConnection()));
    connect(this, SIGNAL(testingParameters(QString,QString,QString)), db, SLOT(testMysqlConnection(QString ,QString ,QString )));

    connect(ui->mysql_ssh_testConnection_btn, SIGNAL(clicked()), this, SLOT(emitSSHConnectionSignal()));
    connect(this, SIGNAL(sendSSHParameters(QString, QString, QString)), ssh, SLOT(testSSHConnection(QString,QString,QString)));
}

mysqlSettings::~mysqlSettings()
{
    delete ui;
}

void mysqlSettings::testingConnection()
{
    mysqlParameters.ipAddress = ui->mysql_host->text();
    mysqlParameters.username = ui->mysql_username->text();
    mysqlParameters.password = ui->mysql_password->text();
    emit testingParameters(mysqlParameters.ipAddress, mysqlParameters.username, mysqlParameters.password);
}

void mysqlSettings::emitSSHConnectionSignal()
{
    ssh->setSSHHost(ui->mysql_backup_ip->text());
    ssh->setSSHUsername(ui->mysql_backup_username->text());
    ssh->setSSHPassword(ui->mysql_backup_password->text());
    emit sendSSHParameters(ssh->getSSHHost(), ssh->getSSHUsername(), ssh->getSSPassword());
}

void mysqlSettings::tryingToConnect()
{
    mysqlParameters.ipAddress = ui->mysql_host->text();
    mysqlParameters.username = ui->mysql_username->text();
    mysqlParameters.password = ui->mysql_password->text();
    emit sendParameters(mysqlParameters.ipAddress, mysqlParameters.username, mysqlParameters.password);
}

void mysqlSettings::enableRemoteAutomaticBackup(bool value)
{
    ui->mysql_timetable_tabwidget->setEnabled(value);
}

void mysqlSettings::createDump()
{

}

void mysqlSettings::loadDefault()
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
