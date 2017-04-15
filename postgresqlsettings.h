#ifndef POSTGRESQLSETTINGS_H
#define POSTGRESQLSETTINGS_H

#include <QDialog>
#include "parameters.h"
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

public slots:
    void tryingToConnect();
    void enableRemoteManaulBackup(bool value);
    void enableRemoteAutomaticBackup(bool value);

private:
    Ui::postgresqlSettings *ui;
    parameters postgreParameters;

};

#endif // POSTGRESQLSETTINGS_H
