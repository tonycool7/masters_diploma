#include "postgresqlsettings.h"
#include "ui_postgresqlsettings.h"

postgresqlSettings::postgresqlSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::postgresqlSettings)
{
    ui->setupUi(this);
    setFixedSize(841, 550);
    for(int i = 0; i < 4; i++){
        ui->postgre_timetable_tabwidget->setTabEnabled(i, false);
    }

    DatabaseManager *db = new PostgreSQLDatabaseManager();
    ssh = new sshManager();

    connect(ui->loadDefault, SIGNAL(clicked()), this, SLOT(loadPostgreSQLDefault()));
    connect(ui->loadDefault2, SIGNAL(clicked()), this, SLOT(loadSSHDefault()));

    connect(ui->postgre_dynamic_configNaming, SIGNAL(toggled(bool)), ui->postgre_configuration_name, SLOT(setDisabled(bool)));
    connect(ui->postgre_ok_btn, SIGNAL(clicked()), this, SLOT(tryingToConnect()));
    connect(this, SIGNAL(sendParameters(QString,QString,QString)), db, SLOT(connectToServer(QString,QString,QString)));
    connect(ui->postgre_cancel_btn, SIGNAL(clicked()), this, SLOT(close()));

    connect(ui->postgre_test_connection_btn, SIGNAL(clicked()), this, SLOT(testingConnection()));
    connect(this, SIGNAL(testingParameters(QString,QString,QString)), db, SLOT(testConnection(QString ,QString ,QString)));

    connect(ui->postgre_backup_test_btn, SIGNAL(clicked()), this, SLOT(emitSSHConnectionSignal()));
    connect(this, SIGNAL(sendSSHParameters(QString, QString, QString)), ssh, SLOT(testSSHConnection(QString,QString,QString)));
}

void postgresqlSettings::setHost(QString value)
{
    host = value;
}

void postgresqlSettings::setUsername(QString value)
{
    username = value;
}

void postgresqlSettings::setPassword(QString value)
{
    password = value;
}

void postgresqlSettings::setPort(QString value)
{
    port = value;
}

QString postgresqlSettings::getHost()
{
    return host;
}

QString postgresqlSettings::getUsername()
{
    return username;
}

QString postgresqlSettings::getPassword()
{
    return password;
}

QString postgresqlSettings::getPort()
{
    return port;
}

postgresqlSettings::~postgresqlSettings()
{
    delete ui;
}

void postgresqlSettings::testingConnection()
{
    setHost(ui->postgre_host->text());
    setUsername(ui->postgre_username->text());
    setPassword(ui->postgre_password->text());
    emit testingParameters(getHost(), getUsername(), getPassword());
}

void postgresqlSettings::loadPostgreSQLDefault()
{
    ui->postgre_host->setText("localhost");
    ui->postgre_username->setText("root");
    ui->postgre_password->setText("dlords");
}

void postgresqlSettings::loadSSHDefault()
{
    ui->postgre_backup_ip->setText("192.168.1.194");
    ui->postgre_backup_username->setText("root");
    ui->postgre_backup_password->setText("dlords");
}

void postgresqlSettings::tryingToConnect()
{
    setHost(ui->postgre_host->text());
    setUsername(ui->postgre_username->text());
    setPassword(ui->postgre_password->text());
    emit sendParameters(getHost(), getUsername(), getPassword());
}

void postgresqlSettings::enableRemoteManaulBackup(bool value)
{
     ui->postgre_destination_settings->setEnabled(value);
}

void postgresqlSettings::enableRemoteAutomaticBackup(bool value)
{
    ui->postgre_timetable_tabwidget->setEnabled(value);
}

void postgresqlSettings::emitSSHConnectionSignal()
{
    ssh->setSSHHost(ui->postgre_backup_ip->text());
    ssh->setSSHUsername(ui->postgre_backup_username->text());
    ssh->setSSHPassword(ui->postgre_backup_password->text());
    emit sendSSHParameters(ssh->getSSHHost(), ssh->getSSHUsername(), ssh->getSSPassword());
}
