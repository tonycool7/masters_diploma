#include "sshmanager.h"

QString sshManager::host = "";
QString sshManager::username = "";
QString sshManager::password = "";
sshManager *sshManager::sshInstance = 0;

sshManager::sshManager(QWidget *parent)
{
    msg = new QMessageBox(this);
    publicKeyAuth = false;
    if(notify == NULL){
        notify = new notifier();
        notify->connectToBackupSystem("192.168.1.194");
    }
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



void sshManager::sendBackupToRemoteSSHServer(QString host, QString username, QString password, QString folder)
{
    if(zip.Zipped(folder)){
        QString filename="send.sh";
        QFile file(filename);
        QProcess *send = new QProcess();
        if(file.open(QIODevice::WriteOnly | QIODevice::Text)){
            QTextStream out(&file);
            out << "#!/bin/sh\n";
            if(publicKeyAuth){
                out << "scp "+zip.returnAllBackups(folder)+" "<<username<<"@"<<host<<":/diplom/p2p/backup/" ;
            }else{
                out << "sshpass -p"<<password<<" scp "+zip.returnAllBackups(folder)+" "<<username<<"@"<<host<<":/diplom/p2p/backup/" ;
            }
            file.close();
        }
        send->start("/bin/sh" , QStringList() <<"send.sh");
        send->waitForFinished();
        send->close();
        deleteAllSQLFiles(folder);
        notify->sendNotification();
    }else{
        qDebug() << "zip error";
    }
}

void sshManager::deleteAllSQLFiles(QString folder)
{
    QString filename="delete.sh";
    QFile file(filename);
    QProcess *deleteSQLFiles = new QProcess();
    if(file.open(QIODevice::WriteOnly | QIODevice::Text)){
        QTextStream out(&file);
        out << "#!/bin/sh\n";
        out << "rm "<<folder<<"/*.sql" ;
        file.close();
    }
    deleteSQLFiles->start("/bin/sh" , QStringList() <<"delete.sh");
    deleteSQLFiles->waitForFinished();
    deleteSQLFiles->close();
}

sshManager *sshManager::getSSHManager()
{
    if(!sshInstance){
        sshInstance = new sshManager();
    }
    return sshInstance;
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
    //rc = ssh_userauth_password(my_ssh_session, NULL, password.toStdString().c_str());
    //int rc;
    rc = ssh_userauth_autopubkey(my_ssh_session, "");
    if (rc == SSH_AUTH_ERROR)
    {
        rc = ssh_userauth_password(my_ssh_session, NULL,  password.toStdString().c_str());
        if(rc == SSH_AUTH_ERROR){
            QMessageBox::critical(this, tr("Testing connection to SSH server"),tr(ssh_get_error(my_ssh_session)), QMessageBox::Ok, QMessageBox::Ok);
            ssh_disconnect(my_ssh_session);
            return false;
        }else{
             publicKeyAuth = false;
            QMessageBox::information(this, tr("Testing connection to SSH server"), tr("Connection successfull"), QMessageBox::Ok, QMessageBox::Ok);
            ssh_disconnect(my_ssh_session);
            return true;
        }
    }else{
        publicKeyAuth = true;
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

