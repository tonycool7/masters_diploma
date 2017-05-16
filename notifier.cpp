#include "notifier.h"

notifier::notifier(QObject *parent) : QObject(parent)
{

}

void notifier::sendNotification()
{
    byte.append("103");
    socket->write(byte);
    byte.clear();
    socket->flush();
}

void notifier::receiveConfirmation()
{
    QByteArray data = socket->readAll();
    qDebug() << data;
}

void notifier::connectToBackupSystem(QString ip)
{
    socket = new QTcpSocket;
    socket->connectToHost(ip,81);

    QObject::connect(socket,SIGNAL(connected()),this,SLOT(success()));
    QObject::connect(socket,SIGNAL(readyRead()),this,SLOT(receiveConfirmation()));
}

notifier::~notifier()
{

}

void notifier::success()
{
    qDebug() << "successfully connected";
}

