#include "zip.h"
#include <QDebug>

Zip::Zip()
{

}

bool Zip::Zipped()
{
    QString filename="zipper.sh";
    QFile file(filename);
    QProcess *zip = new QProcess;
    if(file.open(QIODevice::WriteOnly | QIODevice::Text)){
        QTextStream out(&file);
        out << "#!/bin/sh\n";
        out << "zip mySQLRemote/backup_"+QDate::currentDate().toString("MM_dd_yyyy")+"+"+QDateTime::currentDateTime().toString("hh:mm:ss")+".zip"+returnAllFiles();
        file.close();
    }
    int result = zip->execute("/bin/sh" , QStringList() <<"zipper.sh");
    zip->waitForFinished();

    if(result == 0)
        return true;

    return false;
}

QString Zip::returnAllFiles(){
    QDir dir("/home/tony/qt/build-Diplom-Desktop_Qt_5_7_0_GCC_64bit-Debug/mySQLRemote");
    dir.setNameFilters(QStringList()<<"*.sql");
    QString files = "";
    QFileInfoList list = dir.entryInfoList();
    for (int i = 0; i < list.size(); ++i) {
        QFileInfo fileInfo = list.at(i);
        files += " mySQLRemote/"+fileInfo.fileName();
    }

    return files;
}

QString Zip::returnAllBackups(){
    QDir dir("/home/tony/qt/build-Diplom-Desktop_Qt_5_7_0_GCC_64bit-Debug/mySQLRemote");
    dir.setNameFilters(QStringList()<<"*.zip");
    QString files = "";
    QFileInfoList list = dir.entryInfoList();
    for (int i = 0; i < list.size(); ++i) {
        QFileInfo fileInfo = list.at(i);
        files += " mySQLRemote/"+fileInfo.fileName();
    }

    return files;
}
