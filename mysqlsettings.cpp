#include "mysqlsettings.h"
#include "ui_mysqlsettings.h"

mysqlSettings::mysqlSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mysqlSettings)
{
    ui->setupUi(this);
    setFixedSize(841, 550);
    for(int i = 0; i < 4; i++){
        ui->mysql_timetable_tabwidget->setTabEnabled(i, false);
    }
    DatabaseManager *db = new DatabaseManager();

    connect(ui->mysql_cancel_btn, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->mysql_ok_btn, SIGNAL(clicked()), this, SLOT(tryingToConnect()));
    connect(this, SIGNAL(sendParameters(QString,QString,QString)), db, SLOT(connectToMysqlServer(QString ,QString ,QString )));

    connect(ui->mysql_test_connection_btn, SIGNAL(clicked()), this, SLOT(testingConnection()));
    connect(this, SIGNAL(testingParameters(QString,QString,QString)), db, SLOT(testConnection(QString ,QString ,QString )));
}

mysqlSettings::~mysqlSettings()
{
    delete ui;
}

void mysqlSettings::testingConnection()
{
    mysqlParameters.ipAddress = ui->mysql_host->text();
    mysqlParameters.username = ui->mysql_username->text();
    mysqlParameters.password = ui->mysql_password->text();
    emit testingParameters(mysqlParameters.ipAddress, mysqlParameters.username, mysqlParameters.password);
}

void mysqlSettings::tryingToConnect()
{
    mysqlParameters.ipAddress = ui->mysql_host->text();
    mysqlParameters.username = ui->mysql_username->text();
    mysqlParameters.password = ui->mysql_password->text();
    emit sendParameters(mysqlParameters.ipAddress, mysqlParameters.username, mysqlParameters.password);
}

void mysqlSettings::enableRemoteAutomaticBackup(bool value)
{
    ui->mysql_timetable_tabwidget->setEnabled(value);
}

void mysqlSettings::enableRemoteManaulBackup(bool value)
{
    ui->mysql_destination_details->setEnabled(value);
}
