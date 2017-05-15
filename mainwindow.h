#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mysqlsettings.h"
#include "postgresqlsettings.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    static int tab;
    ~MainWindow();

private:
    Ui::MainWindow *ui;

private slots:
    void update(int value);

};

#endif // MAINWINDOW_H
