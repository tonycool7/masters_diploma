#ifndef POSTGRESQLSETTINGS_H
#define POSTGRESQLSETTINGS_H

#include <QDialog>
#include "parameters.h"
#include "sshmanager.h"
#include "databasemanager.h"


namespace Ui {
class postgresqlSettings;
}

class postgresqlSettings : public QDialog
{
    Q_OBJECT

public:
    explicit postgresqlSettings(QWidget *parent = 0);
    ~postgresqlSettings();

signals:
    void sendParameters(QString, QString, QString);
    void testingParameters(QString, QString, QString);
    void sendSSHParameters(QString, QString, QString);

public slots:
    void testingConnection();
    void tryingToConnect();
    void enableRemoteManaulBackup(bool value);
    void enableRemoteAutomaticBackup(bool value);
    void emitSSHConnectionSignal();

private:
    Ui::postgresqlSettings *ui;
    parameters postgreParameters;
    sshManager *ssh;

};

#endif // POSTGRESQLSETTINGS_H
