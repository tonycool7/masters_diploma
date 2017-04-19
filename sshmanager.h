#ifndef SSHMANAGER_H
#define SSHMANAGER_H

#include <QString>
#include <QDialog>
#include <QDebug>
#include <libssh/libssh.h>
#include <QMessageBox>
#include <QFile>
#include <QProcess>
#include <QTextStream>


class sshManager : public QDialog
{
    Q_OBJECT

public:
    explicit sshManager(QWidget *parent = 0);
    ~sshManager();
    void setSSHHost(QString host_value);
    void setSSHUsername(QString username_value);
    void setSSHPassword(QString password_value);
    void sendBackupToRemoteSSHServer(QString host,QString username ,QString password);
    QString getSSHHost();
    QString getSSHUsername();
    QString getSSPassword();

private:
    QString host;
    QString username;
    QString password;
    QMessageBox *msg;

public slots:
    void testSSHConnection(QString host,QString username ,QString password);

};

#endif // SSHMANAGER_H
