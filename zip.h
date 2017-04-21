#ifndef ZIP_H
#define ZIP_H

#include <QVector>
#include <QFile>
#include <QProcess>
#include <QTextStream>
#include <QDir>

class Zip
{
public:
    Zip();
    void Zipped();
    QString returnAllFiles();
};

#endif // ZIP_H
