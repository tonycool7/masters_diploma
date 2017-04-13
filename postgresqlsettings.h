#ifndef POSTGRESQLSETTINGS_H
#define POSTGRESQLSETTINGS_H

#include <QDialog>

namespace Ui {
class postgresqlSettings;
}

class postgresqlSettings : public QDialog
{
    Q_OBJECT

public:
    explicit postgresqlSettings(QWidget *parent = 0);
    ~postgresqlSettings();

private:
    Ui::postgresqlSettings *ui;
};

#endif // POSTGRESQLSETTINGS_H
