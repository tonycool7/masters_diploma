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
    DatabaseManager *db = new DatabaseManager();
    connect(ui->mysql_ok_btn, SIGNAL(clicked()), db, SLOT(connectToMysqlServer()));
}

mysqlSettings::~mysqlSettings()
{
    delete ui;
}
