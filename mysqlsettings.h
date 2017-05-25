#ifndef MYSQLSETTINGS_H
#define MYSQLSETTINGS_H

#include <QDialog>
#include "mysqldatabasemanager.h"

namespace Ui {
class mysqlSettings;
}

class mysqlSettings : public QDialog
{
    Q_OBJECT

public:
    explicit mysqlSettings(QWidget *parent = 0);
    ~mysqlSettings();
    void setHost(QString value);
    void setUsername(QString value);
    void setPassword(QString value);
    void setPort(QString value);
    QString getHost();
    QString getUsername();
    QString getPassword();
    QString getPort();

signals:
    void sendParameters(QString, QString, QString);
    void testingParameters(QString, QString, QString);
    void storeInMySQLRemoteBackupFolder(bool);

public slots:
    void testingConnection();
    void enableRemoteManaulBackup(bool value);
    void enableRemoteAutomaticBackup(bool value);
    void loadMySQLDefault();

private:
    Ui::mysqlSettings *ui;
    QString username;
    QString password;
    QString configFilename;
    QString port;
    QString host;

};

#endif // MYSQLSETTINGS_H
