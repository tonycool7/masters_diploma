#include "notifier.h"

notifier::notifier()
{

}

bool notifier::sendNotification()
{
    request_code = "103";
    status = write(socket_id,request_code, sizeof(request_code));
    if (status < 0)
        qDebug() << "sending error";
        return false;

    bzero(buffer,256);
    status = read(socket_id,buffer,255);
    if (status < 0)
        qDebug() << "sending error";
        return false;

    return buffer == "ok" ? true : false;
}

bool notifier::createSocket()
{
    socket_id = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if(socket_id < 0)
    {
        qDebug() << "socket error";
        return false;
    }
    return true;
}

bool notifier::connectToBackupServer(QString ip)
{
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    status = getaddrinfo("192.168.1.194", "81", &hints, &res);
    if(status != 0)
    {
        qDebug() << "connect error";
        return false;
    }
    status = connect(socket_id, res->ai_addr, res->ai_addrlen);
    if(status < 0)
    {
        qDebug() << "connect error";
        return false;
    }
    return true;
}

notifier::~notifier()
{
    close(socket_id);
}
