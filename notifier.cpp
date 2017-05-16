#include "notifier.h"

notifier::notifier()
{
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
}

bool notifier::sendNotification()
{
    char buffer[256];
    request_code = "103";
    status = write(getSocketId(),request_code, sizeof(request_code));
    if (status < 0)
        qDebug() << "sending error";
        return false;

    bzero(buffer,256);
    status = read(getSocketId(),buffer,255);
    if (status < 0)
        qDebug() << "sending error";
        return false;

    qDebug() << buffer;
    close(getSocketId());
    return true;
}

bool notifier::createSocket()
{
    int id;
    id = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if(id < 0)
    {
        qDebug() << "socket error";
        return false;
    }
    setSocketId(id);
    return true;
}

void notifier::setSocketId(int socket)
{
    socket_id = socket;
}

int notifier::getSocketId()
{
    return socket_id;
}

bool notifier::connectToBackupServer(QString ip)
{
    status = getaddrinfo("192.168.1.194", "81", &hints, &res);
    if(status != 0)
    {
        qDebug() << "connect error 1";
        return false;
    }
    if(createSocket() < 0){
        return false;
    }

    if(createSocket()){
        status = connect(getSocketId(), res->ai_addr, res->ai_addrlen);
        if(status < 0)
        {
            qDebug() << "connect error 2";
            return false;
        }
    }

    return true;
}

notifier::~notifier()
{
    close(socket_id);
}
