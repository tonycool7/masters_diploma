#ifndef NOTIFIER_H
#define NOTIFIER_H

#include <QObject>
#include <QTcpSocket>
#include <QDebug>

class notifier : public QObject
{

    Q_OBJECT

public:
    explicit notifier(QObject *parent = 0);
    void connectToBackupSystem(QString ip);

    ~notifier();

signals:

public slots:
    void success();
    void sendNotification();
    void receiveConfirmation();


private:
    QTcpSocket *socket;
    QByteArray byte;

public slots:
};

#endif // NOTIFIER_H
