#include "mainwindow.h"
#include <QApplication>
#include "sshmanager.h"

QString sshManager::host = "";
QString sshManager::username = "";
QString sshManager::password = "";

int main(int argc, char *argv[])
{
    signal(SIGPIPE, SIG_IGN);
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
