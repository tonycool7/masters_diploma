#include "mysqlsettings.h"
#include "ui_mysqlsettings.h"

mysqlSettings::mysqlSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mysqlSettings)
{
    ui->setupUi(this);
}

mysqlSettings::~mysqlSettings()
{
    delete ui;
}
