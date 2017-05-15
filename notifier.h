#ifndef NOTIFIER_H
#define NOTIFIER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <QDebug>
#include <arpa/inet.h>

struct addrinfo hints, *res;

class notifier
{
public:
    notifier();
    notifier(QString ip);
    bool sendNotification();
    bool createSocket();
    bool connectToBackupServer(QString ip);

    ~notifier();

signals:


private:
    int status;
    int socket_id;
    QString backupServerIp;
    char buffer[256];
    char *request_code;

public slots:
};

#endif // NOTIFIER_H
