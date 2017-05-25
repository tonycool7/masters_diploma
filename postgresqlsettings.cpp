#include "postgresqlsettings.h"
#include "ui_postgresqlsettings.h"

postgresqlSettings::postgresqlSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::postgresqlSettings)
{
    ui->setupUi(this);
    setFixedSize(841, 550);

    DatabaseManager *db = new PostgreSQLDatabaseManager();

//    connect(ui->daily_pos, SIGNAL(toggled(bool)), this, SLOT(setDaily(bool)));
//    connect(ui->weekly_pos, SIGNAL(toggled(bool)), this, SLOT(setWeekly(bool)));
//    connect(ui->monthly_pos, SIGNAL(toggled(bool)), this, SLOT(setMonthly(bool)));
//    connect(ui->yearly_pos, SIGNAL(toggled(bool)), this, SLOT(setYearly(bool)));

    connect(ui->loadDefault, SIGNAL(clicked()), this, SLOT(loadPostgreSQLDefault()));

    connect(ui->postgre_ok_btn, SIGNAL(clicked()), this, SLOT(tryingToConnect()));
    connect(this, SIGNAL(sendParameters(QString,QString,QString)), db, SLOT(connectToServer(QString ,QString ,QString )));

    connect(ui->postgre_dynamic_configNaming, SIGNAL(toggled(bool)), ui->postgre_configuration_name, SLOT(setDisabled(bool)));
    connect(this, SIGNAL(sendParameters(QString,QString,QString)), db, SLOT(connectToServer(QString,QString,QString)));
    connect(ui->postgre_cancel_btn, SIGNAL(clicked()), this, SLOT(close()));

    connect(ui->postgre_test_connection_btn, SIGNAL(clicked()), this, SLOT(testingConnection()));
    connect(this, SIGNAL(testingParameters(QString,QString,QString)), db, SLOT(testConnection(QString ,QString ,QString)));

}

void postgresqlSettings::setHost(QString value)
{
    host = value;
}

void postgresqlSettings::setUsername(QString value)
{
    username = value;
}

void postgresqlSettings::setPassword(QString value)
{
    password = value;
}

void postgresqlSettings::setPort(QString value)
{
    port = value;
}

QString postgresqlSettings::getHost()
{
    return host;
}

QString postgresqlSettings::getUsername()
{
    return username;
}

QString postgresqlSettings::getPassword()
{
    return password;
}

QString postgresqlSettings::getPort()
{
    return port;
}

postgresqlSettings::~postgresqlSettings()
{
    delete ui;
}

void postgresqlSettings::testingConnection()
{
    setHost(ui->postgre_host->text());
    setUsername(ui->postgre_username->text());
    setPassword(ui->postgre_password->text());
    emit testingParameters(getHost(), getUsername(), getPassword());
}

void postgresqlSettings::loadPostgreSQLDefault()
{
    ui->postgre_host->setText("localhost");
    ui->postgre_username->setText("root");
    ui->postgre_password->setText("dlords");
}

void postgresqlSettings::tryingToConnect()
{
    setHost(ui->postgre_host->text());
    setUsername(ui->postgre_username->text());
    setPassword(ui->postgre_password->text());
    emit sendParameters(getHost(), getUsername(), getPassword());
}

void postgresqlSettings::showDomainField(bool value)
{
    ui->postgre_destination_settings->setEnabled(value);
    ui->postgre_timetable->setEnabled(value);
    ui->postgre_timetable_tabwidget->setEnabled(value);
}

void postgresqlSettings::setMonthly(bool value)
{
    ui->postgre_timetable_tabwidget->setTabEnabled(2, value);
}


void postgresqlSettings::setDaily(bool value)
{
    ui->postgre_timetable_tabwidget->setTabEnabled(0, value);
}

void postgresqlSettings::setWeekly(bool value)
{
    ui->postgre_timetable_tabwidget->setTabEnabled(1, value);
}

void postgresqlSettings::setYearly(bool value)
{
    ui->postgre_timetable_tabwidget->setTabEnabled(3, value);
}
