#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = 0);
    QTcpServer s;
    QList<QTcpSocket*> clients;
    QList<int> users;
    QByteArray b;
};

#endif // SERVER_H
