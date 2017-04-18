#ifndef MYSQLSETTINGS_H
#define MYSQLSETTINGS_H

#include <QDialog>
#include "parameters.h"
#include "databasemanager.h"
#include "sshmanager.h"

namespace Ui {
class mysqlSettings;
}

class mysqlSettings : public QDialog
{
    Q_OBJECT

public:
    explicit mysqlSettings(QWidget *parent = 0);
    parameters getMysqlParameters();
    ~mysqlSettings();

signals:
    void sendParameters(QString, QString, QString);
    void testingParameters(QString, QString, QString);
    void sendSSHParameters(QString, QString, QString);
    void testingSSHParameters();

public slots:
    void testingConnection();
    void emitSSHConnectionSignal();
    void tryingToConnect();
    void enableRemoteManaulBackup(bool value);
    void enableRemoteAutomaticBackup(bool value);
    void createDump();

private:
    Ui::mysqlSettings *ui;
    parameters mysqlParameters;
    QMessageBox *msg;
    sshManager *ssh;

};

#endif // MYSQLSETTINGS_H
