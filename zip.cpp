#include "zip.h"
#include <QDebug>

Zip::Zip()
{

}

bool Zip::Zipped(QString folder)
{
    QString filename="zipper.sh";
    QFile file(filename);
    QProcess *zip = new QProcess;
    if(file.open(QIODevice::WriteOnly | QIODevice::Text)){
        QTextStream out(&file);
        out << "#!/bin/sh\n";
        out << "zip "+folder+"/backup_"+QDate::currentDate().toString("MM_dd_yyyy")+"+"+QDateTime::currentDateTime().toString("hh:mm:ss")+".zip"+returnAllFiles(folder);
        out << "\nchmod -R 777 "+folder+"/backup_"+QDate::currentDate().toString("MM_dd_yyyy")+"+"+QDateTime::currentDateTime().toString("hh:mm:ss")+".zip";
        file.close();
    }
    int result = zip->execute("/bin/sh" , QStringList() <<"zipper.sh");
    zip->waitForFinished();

    if(result == 0)
        return true;

    return false;
}

QString Zip::returnAllFiles(QString folder){
    QDir dir("/home/tony/qt/build-Diplom-Desktop_Qt_5_7_0_GCC_64bit-Debug/"+folder);
    dir.setNameFilters(QStringList()<<"*.sql");
    QString files = "";
    QFileInfoList list = dir.entryInfoList();
    for (int i = 0; i < list.size(); ++i) {
        QFileInfo fileInfo = list.at(i);
        files += " "+folder+"/"+fileInfo.fileName();
    }
    return files;
}

QString Zip::returnAllBackups(QString folder){
    QDir dir("/home/tony/qt/build-Diplom-Desktop_Qt_5_7_0_GCC_64bit-Debug/"+folder);
    dir.setNameFilters(QStringList()<<"*.zip");
    QString files = "";
    QFileInfoList list = dir.entryInfoList();
    for (int i = 0; i < list.size(); ++i) {
        QFileInfo fileInfo = list.at(i);
        files += " "+folder+"/"+fileInfo.fileName();
    }

    return files;
}
