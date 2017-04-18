#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    signal(SIGPIPE, SIG_IGN);
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
