#ifndef MYSQLSETTINGS_H
#define MYSQLSETTINGS_H

#include <QDialog>
#include "parameters.h"
#include "databasemanager.h"
#include <libssh/libssh.h>
#include <QFile>
#include <QProcess>
#include <QTextStream>
#include <QMessageBox>

namespace Ui {
class mysqlSettings;
}

class mysqlSettings : public QDialog
{
    Q_OBJECT

public:
    explicit mysqlSettings(QWidget *parent = 0);
    void setMysqlConnectParameters(QString host,QString username ,QString password, QString port);
    parameters getMysqlParameters();
    ~mysqlSettings();

signals:
    void sendParameters(QString, QString, QString);
    void testingParameters(QString, QString, QString);
    void sendSSHParameters(QString, QString, QString);
    void testingSSHParameters();

public slots:
    void testingConnection();
    void testingSSHConnectionSignal();
    void testingSSHConnection(QString, QString, QString);
    void tryingToConnect();
    void tryingToConnectSSH();
    void enableRemoteManaulBackup(bool value);
    void enableRemoteAutomaticBackup(bool value);
    void sendBackupToRemoteSSHServer(QString host,QString username ,QString password);
    void createDump();

private:
    Ui::mysqlSettings *ui;
    parameters mysqlParameters;
    QMessageBox *msg;

};

#endif // MYSQLSETTINGS_H
