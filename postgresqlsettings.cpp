#include "postgresqlsettings.h"
#include "ui_postgresqlsettings.h"

postgresqlSettings::postgresqlSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::postgresqlSettings)
{
    ui->setupUi(this);
}

postgresqlSettings::~postgresqlSettings()
{
    delete ui;
}
