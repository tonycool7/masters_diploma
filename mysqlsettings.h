#ifndef MYSQLSETTINGS_H
#define MYSQLSETTINGS_H

#include <QDialog>
#include "parameters.h"

namespace Ui {
class mysqlSettings;
}

class mysqlSettings : public QDialog
{
    Q_OBJECT

public:
    explicit mysqlSettings(QWidget *parent = 0);
    ~mysqlSettings();

private:
    Ui::mysqlSettings *ui;
    parameters mysqlParameters;

};

#endif // MYSQLSETTINGS_H
