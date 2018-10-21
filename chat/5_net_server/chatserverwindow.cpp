#include "chatserverwindow.h"
#include "ui_chatserverwindow.h"

#include <QFileDialog>
#include <QStringList>
#include <math.h>
#include <time.h>

//int ID;

bool busy[32];

ChatServerWindow::ChatServerWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ChatServerWindow)
{
    ui->setupUi(this);

    connect(&server, SIGNAL(newConnection()), SLOT(onNewConnection()));
    checkServerState();
}
//------------------------------------------------------------------------------
ChatServerWindow::~ChatServerWindow()
{
    server.close();
    for(int a=0; a<clients.size(); a++)
    {
        clients[a]->deleteLater();
    }
    clients.clear();
    delete ui;
}
//------------------------------------------------------------------------------
void ChatServerWindow::on_openPort_button_clicked()
{
    if(server.isListening())
    {
        server.close();
        ui->log_edit->append(QString::fromUtf8("Порт закрыт."));
    }
    else
    {
        server.listen(QHostAddress::Any, ui->port_sb->value());
        ui->log_edit->append(QString::fromUtf8("Сервер запущен на порту ")
                             + QString::number(ui->port_sb->value()));
    }
    checkServerState();
}

//------------------------------------------------------------------------------
void ChatServerWindow::checkServerState()
{
    if(server.isListening())
        ui->openPort_button->setText(QString::fromUtf8("Закрыть порт"));
    else
        ui->openPort_button->setText(QString::fromUtf8("Открыть порт"));
}
//------------------------------------------------------------------------------
void ChatServerWindow::onNewConnection()
{
//    for (i=0;i<32;i++)
//    {
//        if (users[i]!=i)
//        {
//            users[i]=i;
//            int current_id=1;
//            break;
//        }
//    }
    QTcpSocket* s = server.nextPendingConnection();
    if(s == 0)
        return;
    ui->log_edit->append(QString::fromUtf8("Подключен клиент: ")
                         + s->peerAddress().toString() + ":"
                         + QString::number(s->peerPort()));

    connect(s, SIGNAL(disconnected()), SLOT(onSocketDisconnected()));
    connect(s, SIGNAL(readyRead()), SLOT(onClientDataReady()));

    clients.append(s);
    users.append(-1);

//    int ID=0;
//    for(int i=0;i<32;i++)
//    {
//        if(busy[i]==0)
//        {
//            ID=i;
//            break;
//        }
//    }

//    QString str=QString::number(ID);

//    b=str.toUtf8();

//    clients[clients.size()-1]->write(b);

//    busy[ID]=1;

    for(int a=0; a<clients.size(); a++)
    {
        if (busy[a]==false)
        {
            users[clients.size()-1]=a;
            QString str=QString::number(a);
            b = str.toUtf8();
            clients[a]->write(b);
            busy[a]=true;

        }
//        if(clients[a] == s)
//        {
//            users[a]=a;
//            QString str=QString::number(a);
//            b = str.toUtf8();
//            clients[a]->write(b);
//            break;
//        }
    }


//    QString str="5"/*QString::number(1)*/;
//    QByteArray b = str.toUtf8();
//    for(int a=0; a<clients.size(); a++)
//    {
//        QString str=QString::number(1);
//        b = str.toUtf8();
//        clients[a]->write(b);
//        ui->log_edit->append(b);
//    }
    ui->log_edit->append(b);
}
//------------------------------------------------------------------------------
void ChatServerWindow::onClientDataReady()
{
    QObject *s = sender();
    if(s == 0)
        return;
    if(!s->inherits("QTcpSocket"))
        return;

//    QByteArray m = QByteArray::users[a];

    QTcpSocket *ss = (QTcpSocket*)s;
    QByteArray ar = ss->readAll();



    QString sign = ss->peerAddress().toString() + ":"
                   + QString::number(ss->peerPort()) + " | ";
    int currentUser=ss->peerAddress().toString().toInt();

    ui->log_edit->append(sign + QString::fromUtf8(ar));
    // Рассылаем сообщение всем (надо не всем, раскомментить)


    for(int a=0; a<clients.size(); a++)
    {
//        if(clients[a] != ss)
//        if(a==currentUser)
//            continue;
        clients[a]->write(ar);
    }
}
//------------------------------------------------------------------------------
void ChatServerWindow::onSocketDisconnected()
{
    QObject *s = sender();
    if(s->inherits("QTcpSocket"))
    {
        QTcpSocket *ss = (QTcpSocket*)s;
        ss->disconnectFromHost();
        for(int a=0; a<clients.size(); a++)
        {
            if(clients[a] == ss)
            {
                busy[users[a]]=false;
                clients.removeAt(a);
                users.removeAt(a);                
                break;
            }
        }
        ss->deleteLater();
    }
    ui->log_edit->append(QString::fromUtf8("Клиент отключился"));
}
