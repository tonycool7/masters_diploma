#include "zip.h"
#include <QDebug>

Zip::Zip()
{

}

void Zip::Zipped()
{
    QString filename="zipper.sh";
    QFile file(filename);
    QProcess *zip = new QProcess;
    if(file.open(QIODevice::WriteOnly | QIODevice::Text)){
        QTextStream out(&file);
        out << "#!/bin/sh\n";
        out << "zip remote/backup.zip"+returnAllFiles();
        file.close();
    }
}

QString Zip::returnAllFiles(){
    QDir dir;
    dir.setCurrent(dir.absolutePath()+"/remote");
    dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    QString files = "";
    QFileInfoList list = dir.entryInfoList();
    for (int i = 0; i < list.size(); ++i) {
        QFileInfo fileInfo = list.at(i);
        files += " remote/"+fileInfo.fileName();
    }

    return files;
}
