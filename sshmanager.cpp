#include "sshmanager.h"

sshManager::sshManager(QWidget *parent)
{
    msg = new QMessageBox(this);
}

sshManager::~sshManager()
{

}

void sshManager::setSSHHost(QString host_value)
{
    host = host_value;
}

void sshManager::setSSHUsername(QString username_value)
{
    username = username_value;
}

void sshManager::setSSHPassword(QString password_value)
{
    password = password_value;
}



void sshManager::sendBackupToRemoteSSHServer(QString host, QString username, QString password)
{
    if(zip.Zipped()){
        QString filename="send.sh";
        QFile file(filename);
        QProcess *send = new QProcess();
        if(file.open(QIODevice::WriteOnly | QIODevice::Text)){
            QTextStream out(&file);
            out << "#!/bin/sh\n";
            out << "sshpass -p"<<password<<" scp "+zip.returnAllBackups()+" "<<username<<"@"<<host<<":/backup/" ;
            file.close();
        }
        send->start("/bin/sh" , QStringList() <<"send.sh");
        send->waitForFinished();
        send->close();
        deleteAllSQLFiles();
    }else{
        qDebug() << "zip error";
    }

}

void sshManager::deleteAllSQLFiles()
{
    QString filename="delete.sh";
    QFile file(filename);
    QProcess *deleteSQLFiles = new QProcess();
    if(file.open(QIODevice::WriteOnly | QIODevice::Text)){
        QTextStream out(&file);
        out << "#!/bin/sh\n";
        out << "rm mySQLRemote/*.sql" ;
        file.close();
    }
    deleteSQLFiles->start("/bin/sh" , QStringList() <<"delete.sh");
    deleteSQLFiles->waitForFinished();
    deleteSQLFiles->close();
}

bool sshManager::testSSHConnection(QString host, QString username, QString password)
{
    ssh_session my_ssh_session;
    int verbosity = SSH_LOG_PROTOCOL;
    int rc;
    int port =22;
    my_ssh_session = ssh_new();
    if (my_ssh_session == NULL)
      exit(-1);

    ssh_options_set(my_ssh_session, SSH_OPTIONS_HOST, host.toStdString().c_str());
    ssh_options_set(my_ssh_session, SSH_OPTIONS_USER, username.toStdString().c_str());
    ssh_options_set(my_ssh_session, SSH_OPTIONS_LOG_VERBOSITY, &verbosity);
    ssh_options_set(my_ssh_session, SSH_OPTIONS_PORT, &port);
    rc = ssh_connect(my_ssh_session);
    rc = ssh_userauth_password(my_ssh_session, NULL, password.toStdString().c_str());
    if (rc != 0)
    {
     QMessageBox::critical(this, tr("Testing connection to SSH server"),tr(ssh_get_error(my_ssh_session)), QMessageBox::Ok, QMessageBox::Ok);
      ssh_disconnect(my_ssh_session);
      return false;
    }else{
      QMessageBox::information(this, tr("Testing connection to SSH server"), tr("Connection successfull"), QMessageBox::Ok, QMessageBox::Ok);
      ssh_disconnect(my_ssh_session);
      return true;
    }
}

QString sshManager::getSSHHost()
{
    return host;
}

QString sshManager::getSSHUsername()
{
    return username;
}

QString sshManager::getSSPassword()
{
    return password;
}

