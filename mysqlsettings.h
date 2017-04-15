#ifndef MYSQLSETTINGS_H
#define MYSQLSETTINGS_H

#include <QDialog>
#include "parameters.h"
#include "databasemanager.h"

namespace Ui {
class mysqlSettings;
}

class mysqlSettings : public QDialog
{
    Q_OBJECT

public:
    explicit mysqlSettings(QWidget *parent = 0);
    ~mysqlSettings();

signals:
    void sendParameters(QString, QString, QString);
    void testingParameters(QString, QString, QString);

public slots:
    void testingConnection();
    void tryingToConnect();
    void enableRemoteManaulBackup(bool value);
    void enableRemoteAutomaticBackup(bool value);

private:
    Ui::mysqlSettings *ui;
    parameters mysqlParameters;

};

#endif // MYSQLSETTINGS_H
