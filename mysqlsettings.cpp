#include "mysqlsettings.h"
#include "ui_mysqlsettings.h"

mysqlSettings::mysqlSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mysqlSettings)
{
    ui->setupUi(this);
    setFixedSize(444, 675);
    for(int i = 0; i < 4; i++){
        ui->mysql_timetable_tabwidget->setTabEnabled(i, false);
    }
}

mysqlSettings::~mysqlSettings()
{
    delete ui;
}
