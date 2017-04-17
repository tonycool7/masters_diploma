#include "postgresqlsettings.h"
#include "ui_postgresqlsettings.h"

postgresqlSettings::postgresqlSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::postgresqlSettings)
{
    ui->setupUi(this);
    setFixedSize(841, 550);
    for(int i = 0; i < 4; i++){
        ui->postgre_timetable_tabwidget->setTabEnabled(i, false);
    }
    DatabaseManager *db = new DatabaseManager();

    connect(ui->postgre_dynamic_configNaming, SIGNAL(toggled(bool)), ui->postgre_configuration_name, SLOT(setDisabled(bool)));

    connect(ui->postgre_ok_btn, SIGNAL(clicked()), this, SLOT(tryingToConnect()));
    //connect(this, SIGNAL(sendParameters(QString,QString,QString)), db, SLOT(connectToMysqlServer(QString ,QString ,QString )));
}

postgresqlSettings::~postgresqlSettings()
{
    delete ui;
}

void postgresqlSettings::tryingToConnect()
{
    postgreParameters.ipAddress = ui->postgre_host->text();
    postgreParameters.username = ui->postgre_username->text();
    postgreParameters.password = ui->postgre_password->text();
    emit sendParameters(postgreParameters.ipAddress, postgreParameters.username, postgreParameters.password);
}

void postgresqlSettings::enableRemoteManaulBackup(bool value)
{
     ui->postgre_destination_settings->setEnabled(value);
}

void postgresqlSettings::enableRemoteAutomaticBackup(bool value)
{
    ui->postgre_timetable_tabwidget->setEnabled(value);
}
