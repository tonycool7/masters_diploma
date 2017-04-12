#include "mainwindow.h"
#include <QApplication>
#include "mysqlsettings.h"
#include "postgresqlsettings.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

//    mysqlSettings m;
//    postgresqlSettings p;
//    m.show();
//    p.show();
    return a.exec();
}
