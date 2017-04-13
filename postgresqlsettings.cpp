#include "postgresqlsettings.h"
#include "ui_postgresqlsettings.h"

postgresqlSettings::postgresqlSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::postgresqlSettings)
{
    ui->setupUi(this);
    setFixedSize(444, 675);
    for(int i = 0; i < 4; i++){
        ui->postgre_timetable_tabwidget->setTabEnabled(i, false);
    }
}

postgresqlSettings::~postgresqlSettings()
{
    delete ui;
}
