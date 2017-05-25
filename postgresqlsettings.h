#ifndef POSTGRESQLSETTINGS_H
#define POSTGRESQLSETTINGS_H

#include <QDialog>
#include "postgresqldatabasemanager.h"


namespace Ui {
class postgresqlSettings;
}

class postgresqlSettings : public QDialog
{
    Q_OBJECT

public:
    explicit postgresqlSettings(QWidget *parent = 0);
    void setHost(QString value);
    void setUsername(QString value);
    void setPassword(QString value);
    void setPort(QString value);
    QString getHost();
    QString getUsername();
    QString getPassword();
    QString getPort();
    ~postgresqlSettings();

signals:
    void sendParameters(QString, QString, QString);
    void testingParameters(QString, QString, QString);
    void storeInMySQLRemoteBackupFolder(bool);

public slots:
    void testingConnection();
    void loadPostgreSQLDefault();

private:
    Ui::postgresqlSettings *ui;
    QString username;
    QString password;
    QString configFilename;
    QString port;
    QString host;

};


#endif // POSTGRESQLSETTINGS_H
