#ifndef MASTER_H
#define MASTER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <stdlib.h>
#include <string.h>

class master : public QObject
{
    Q_OBJECT
public:
    explicit master(QObject *parent=0);
    QTcpServer server;
    QList<QTcpSocket*> clients;
    QList<int> users;
    QByteArray b;
    int port;

private slots:
    void onNewConnection();
    void onSocketDisconnected();
    void onClientDataReady();
};

#endif // MASTER_H
