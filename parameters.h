#ifndef PARAMETERS_H
#define PARAMETERS_H

#include <QString>

class parameters{
public:
    QString username;
    QString password;
    QString configFilename;
    QString port;
    QString ipAddress;
    QString sshIp;
    QString sshUsername;
    QString sshPort;
    QString sshPassword;
    QString destinationPort;
    QString time;
    QString day;
    QString month;
    bool daily;
    bool weekly;
    bool monthly;
    bool yearly;
    bool dynamicConfigFilename;
};

#endif // PARAMETERS_H
