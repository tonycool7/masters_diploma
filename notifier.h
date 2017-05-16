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

class notifier
{
public:
    notifier();
    notifier(QString ip);
    bool sendNotification();
    bool createSocket();
    void setSocketId(int socket);
    int getSocketId();
    bool connectToBackupServer(QString ip);
    struct addrinfo hints, *res;

    ~notifier();

signals:


private:
    int status;
    int socket_id;
    QString backupServerIp;
    char *request_code;

public slots:
};

#endif // NOTIFIER_H
