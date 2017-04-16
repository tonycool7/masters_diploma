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


    connect(ui->mysql_cancel_btn, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->mysql_ok_btn, SIGNAL(clicked()), this, SLOT(tryingToConnect()));
    connect(this, SIGNAL(sendParameters(QString,QString,QString)), db, SLOT(connectToMysqlServer(QString ,QString ,QString )));

    connect(ui->mysql_test_connection_btn, SIGNAL(clicked()), this, SLOT(testingConnection()));
    connect(this, SIGNAL(testingParameters(QString,QString,QString)), db, SLOT(testConnection(QString ,QString ,QString )));

    connect(ui->mysql_ssh_testConnection_btn, SIGNAL(clicked()), this, SLOT(testingSSHConnectionSignal()));
    connect(this, SIGNAL(sendSSHParameters(QString, QString, QString)), this, SLOT(testingSSHConnection(QString, QString, QString)));
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

void mysqlSettings::testingSSHConnectionSignal()
{
    mysqlParameters.sshIp = ui->mysql_backup_ip->text();
    mysqlParameters.sshUsername = ui->mysql_backup_username->text();
    mysqlParameters.sshPassword = ui->mysql_backup_password->text();
    emit sendSSHParameters(mysqlParameters.sshIp,  mysqlParameters.sshUsername, mysqlParameters.sshPassword);
}

void mysqlSettings::testingSSHConnection(QString host,QString username ,QString password)
{
    ssh_session my_ssh_session;
    int verbosity = SSH_LOG_PROTOCOL;
    int rc;
    int port =22;
    my_ssh_session = ssh_new();
    if (my_ssh_session == NULL)
      exit(-1);

    qDebug() << host;
    qDebug() << username;
    qDebug() << password;
    ssh_options_set(my_ssh_session, SSH_OPTIONS_HOST, host.toStdString().c_str());
    ssh_options_set(my_ssh_session, SSH_OPTIONS_USER, username.toStdString().c_str());
    ssh_options_set(my_ssh_session, SSH_OPTIONS_LOG_VERBOSITY, &verbosity);
    ssh_options_set(my_ssh_session, SSH_OPTIONS_PORT, &port);
    rc = ssh_connect(my_ssh_session);
    rc = ssh_userauth_password(my_ssh_session, NULL, password.toStdString().c_str());
    if (rc != 0)
    {
      msg->critical(this, tr("Testing connection to SSH server"),tr(ssh_get_error(my_ssh_session)), msg->Cancel, msg->Cancel);
      ssh_disconnect(my_ssh_session);
    }else{
      msg->information(this, tr("Testing connection to SSH server"), tr("Connection successfull"), msg->Cancel, msg->Cancel);
      ssh_disconnect(my_ssh_session);
    }
}

void mysqlSettings::tryingToConnect()
{
    mysqlParameters.ipAddress = ui->mysql_host->text();
    mysqlParameters.username = ui->mysql_username->text();
    mysqlParameters.password = ui->mysql_password->text();
    emit sendParameters(mysqlParameters.ipAddress, mysqlParameters.username, mysqlParameters.password);
}

void mysqlSettings::tryingToConnectSSH()
{
    mysqlParameters.sshIp = ui->mysql_backup_ip->text();
    mysqlParameters.sshUsername = ui->mysql_backup_username->text();
    mysqlParameters.sshPassword = ui->mysql_backup_password->text();
    emit sendSSHParameters(mysqlParameters.sshIp,  mysqlParameters.sshUsername, mysqlParameters.sshPassword);
}

void mysqlSettings::enableRemoteAutomaticBackup(bool value)
{
    ui->mysql_timetable_tabwidget->setEnabled(value);
}

void mysqlSettings::createDump()
{

}

void mysqlSettings::sendBackupToRemoteSSHServer(QString host,QString username ,QString password)
{
        QString filename="send.sh";
        QFile file(filename);
        QProcess *send = new QProcess();
        if(file.open(QIODevice::WriteOnly | QIODevice::Text)){
        QTextStream out(&file);
        out << "#!/bin/sh\n";
        out << "sshpass -p"<<password<<" scp dump.sql "<<username<<"@"<<host<<":/backup/" ;
        file.close();
        }

        send->start("/bin/sh" , QStringList() <<"send.sh");
}

void mysqlSettings::enableRemoteManaulBackup(bool value)
{
    ui->mysql_destination_details->setEnabled(value);
}
