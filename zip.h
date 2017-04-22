#ifndef ZIP_H
#define ZIP_H

#include <QVector>
#include <QFile>
#include <QProcess>
#include <QTextStream>
#include <QDir>
#include <QDate>
#include <QDateTime>

class Zip
{
public:
    Zip();
    bool Zipped();
    QString returnAllFiles();
    QString returnAllBackups();
};

#endif // ZIP_H
