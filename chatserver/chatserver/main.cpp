#include <QCoreApplication>
#include <QTcpServer>
#include <QTcpSocket>
#include <stdlib.h>
#include <master.h>


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    master *server=new master();
    return a.exec();
}
