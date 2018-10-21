#include "master.h"
using namespace std;

master::master(QObject *parent) :
    QObject (parent)

{
    port=5600;
    connect(&server, SIGNAL(newConnection()), SLOT(onNewConnection()));
    server.listen(QHostAddress::Any, port);
    printf("Server is launched on port %d\n",port);
}

void master::onNewConnection()
{
//    qDebug()<<"ebat";
    QTcpSocket* s = server.nextPendingConnection();
    if(s == 0)
        return;
    QString c=s->peerAddress().toString()+":"+ QString::number(s->peerPort());
    qDebug()<<c<<" has connect to server";

    connect(s, SIGNAL(disconnected()), SLOT(onSocketDisconnected()));
    connect(s, SIGNAL(readyRead()), SLOT(onClientDataReady()));

    clients.append(s);
}

void master::onSocketDisconnected()
{
    QObject *s = sender();
    QString c;
    if(s->inherits("QTcpSocket"))
    {
        QTcpSocket *ss = (QTcpSocket*)s;

        c=ss->peerAddress().toString()+":"+ QString::number(ss->peerPort());

        ss->disconnectFromHost();
        for(int a=0; a<clients.size(); a++)
        {
            if(clients[a] == ss)
            {
                clients.removeAt(a);
                break;
            }
        }
        ss->deleteLater();
        qDebug()<<c<<" has disconnect from server";
    }    
}

void master::onClientDataReady()
{
    QObject *s = sender();
    if(s == 0)
        return;
    if(!s->inherits("QTcpSocket"))
        return;
    QTcpSocket *ss = (QTcpSocket*)s;
    QByteArray ar = ss->readAll();
    QString c = ss->peerAddress().toString() + ":"
                   + QString::number(ss->peerPort());
    QString message=QString::fromUtf8(ar);
    //qDebug()<<message;


    if(message=="talk")
    {
        qDebug()<<c<<" switch on his microphone";
        return;
    }
    if(message=="quiet")
    {
        qDebug()<<c<<" switch off his microphone";
        return;
    }
    QString f=message.split(" ").first();
    if(f=="text")
    {
        QString temp;
        for(int i=5;i<message.size();i++)
            temp+=message[i];
        qDebug()<<c<<" write "<<temp;
        for(int a=0; a<clients.size(); a++)
        {            
            clients[a]->write(ar);
        }
        return;
    }
    else
    {
        for(int a=0; a<clients.size(); a++)
        {
            if(!(clients[a]->peerAddress()==ss->peerAddress()))
                clients[a]->write(ar);
        }
    }
}
