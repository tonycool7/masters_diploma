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

    DatabaseManager *db = new DatabaseManager();
    ssh = new sshManager();

    connect(ui->loadDefault, SIGNAL(clicked()), this, SLOT(loadDefault()));

    connect(ui->postgre_dynamic_configNaming, SIGNAL(toggled(bool)), ui->postgre_configuration_name, SLOT(setDisabled(bool)));
    connect(ui->postgre_ok_btn, SIGNAL(clicked()), this, SLOT(tryingToConnect()));
    connect(this, SIGNAL(sendParameters(QString,QString,QString)), db, SLOT(connectToPostgreSQLServer(QString,QString,QString)));
    connect(ui->postgre_cancel_btn, SIGNAL(clicked()), this, SLOT(close()));

    connect(ui->postgre_test_connection_btn, SIGNAL(clicked()), this, SLOT(testingConnection()));
    connect(this, SIGNAL(testingParameters(QString,QString,QString)), db, SLOT(testPostgreSQLConnection(QString ,QString ,QString )));

    connect(ui->postgre_backup_test_btn, SIGNAL(clicked()), this, SLOT(emitSSHConnectionSignal()));
    connect(this, SIGNAL(sendSSHParameters(QString, QString, QString)), ssh, SLOT(testSSHConnection(QString,QString,QString)));
}

postgresqlSettings::~postgresqlSettings()
{
    delete ui;
}

void postgresqlSettings::testingConnection()
{
    postgreParameters.ipAddress = ui->postgre_host->text();
    postgreParameters.username = ui->postgre_username->text();
    postgreParameters.password = ui->postgre_password->text();
    emit testingParameters(postgreParameters.ipAddress, postgreParameters.username, postgreParameters.password);
}

void postgresqlSettings::loadDefault()
{
    ui->postgre_host->setText("192.168.1.224");
    ui->postgre_username->setText("root");
    ui->postgre_password->setText("dlords");
}

void postgresqlSettings::tryingToConnect()
{
    postgreParameters.ipAddress = ui->postgre_host->text();
    postgreParameters.username = ui->postgre_username->text();
    postgreParameters.password = ui->postgre_password->text();
    emit sendParameters(postgreParameters.ipAddress, postgreParameters.username, postgreParameters.password);
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
