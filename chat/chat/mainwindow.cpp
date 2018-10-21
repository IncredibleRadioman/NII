#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <ws2tcpip.h>
#include <QHostAddress>
#include <QMessageBox>
#include <QAbstractSocket>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->console,SIGNAL(messageSended()),SLOT(sending()));

    ui->chat->setReadOnly(true);
    ui->address->setReadOnly(true);
    ui->address_2->setReadOnly(true);
    ui->address_3->setReadOnly(true);


    QAudioFormat format;
    format.setSampleRate(48000);
    format.setChannelCount(1);
    format.setSampleSize(16);
    format.setCodec("audio/pcm");
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::UnSignedInt);
    QAudioDeviceInfo info(QAudioDeviceInfo::defaultInputDevice());
        if (!info.isFormatSupported(format))
            format = info.nearestFormat(format);
    input = new QAudioInput(format);
    output = new QAudioOutput(format);

    device = output->start();



    connect(&t,SIGNAL(timeout()),SLOT(sendSpeech()));

    dlg.show();
    int st=dlg.exec();
    if(st==QDialog::Accepted)
    {

        dlg.player->stop();
        nick=dlg.getOut();
        address=dlg.getServer();
        port=dlg.getPORT().toInt();
    }
    else
    {
        dlg.player->stop();
        nick="user";
        address="0.0.0.0";
        port=8080;
    }
    if(nick.isEmpty())
    {
        nick="user";
    }
    if(address.isEmpty())
        address="0.0.0.0";
    if(port==0)
        port=8080;
    ui->address->setText(address);
    ui->address_2->setText(QString::number(port));
    ui->address_3->setText(nick);
    s=new QTcpSocket(this);

}

MainWindow::~MainWindow()
{
    if(isConnected)
    {
        QString serve=nick+" has disconnected from our chat";
        ui->chat->append(serve);
        s->write(serve.toUtf8());
        s->disconnect();
    }
    delete s;
    delete ui;
}

void MainWindow::on_connect_clicked()
{
    if(!isConnected)
    {
//        QString address=ui->address->text();
//        qint16 port=ui->address_2->text().toInt();

        s->bind(QHostAddress::Any,port);
        connect(s, SIGNAL(readyRead()), this, SLOT(receive()));




        s->connectToHost(address,port);
        if(!s->waitForConnected(3000))
        {
            QString path=QDir::currentPath()+"/sounds/no.mp3";
            char* p1=path.toLatin1().data();
            dlg.player->setMedia(QUrl::fromLocalFile(p1));
            dlg.player->setVolume(20);
            dlg.player->play();
            QMessageBox msgBox;
            msgBox.setText("ERROR: "+s->errorString());
            msgBox.exec();
            return;
        }
            //ui->console->output("Connect successful!");
            isConnected=true;
            QString serve="text "+nick+" has connected to our chat";
            s->write(serve.toUtf8());


            QPixmap p(":/icons/connect.png");
            QIcon icon(p);
            ui->connect->setIcon(icon);
            ui->connect->setIconSize(QSize(24,24));
            isSoundRecorded=false;
            QPixmap pix(":/icons/micro2.png");
            QIcon icon1(pix);
            ui->micro->setIcon(icon1);
            ui->micro->setIconSize(QSize(24,24));
            QString path=QDir::currentPath()+"/sounds/t.mp3";
            char* p1=path.toLatin1().data();
            dlg.player->setMedia(QUrl::fromLocalFile(p1));
            dlg.player->setVolume(20);
            dlg.player->play();

    }
    else
    {
        QString serve=nick+" has disconnected from our chat";
        ui->chat->append(serve);
        s->write(serve.toUtf8());

        s->disconnect();
        s->close();
        isConnected=false;
        input->stop();
        QPixmap p(":/icons/disconnect.png");
        QIcon icon(p);
        ui->connect->setIcon(icon);
        ui->connect->setIconSize(QSize(24,24));
        isSoundRecorded=false;
        QPixmap pix(":/icons/micro2.png");
        QIcon icon1(pix);
        ui->micro->setIcon(icon1);
        ui->micro->setIconSize(QSize(24,24));
        QString path=QDir::currentPath()+"/sounds/dmml.mp3";
        char* p1=path.toLatin1().data();
        dlg.player->setMedia(QUrl::fromLocalFile(p1));
        dlg.player->setVolume(20);
        dlg.player->play();
    }
    //sendSpeech();
}

void MainWindow::receive()
{
    QByteArray data;
    data.resize(s->readBufferSize());
    data=s->readAll();
    QString mes=QString::fromUtf8(data).split(" ").first();
    if(mes=="text")
    {
        QStringList temp=QString::fromUtf8(data).split(" ");
        QString ans;
        for(int i=1;i<temp.length()-1;i++)
            ans+=temp[i]+" ";
        ans+=temp[temp.length()-1];
        ui->chat->append(ans);
    }
    else
    {
        if(!isLocked)
        {
            device->write(data.data(), data.size());
        }
    }
}

void MainWindow::sending()
{
    QStringList data=ui->console->CommandList;
    QString mes=data.at(data.length()-1);
    nick=ui->address_3->text();
    mes="text "+nick+": "+mes;
    ui->console->currentCommand=0;
    ui->console->currentPosition=0;
    ui->console->CommandList.clear();
    ui->console->clear();
    if(!isConnected)
    {
        QMessageBox msgBox;
        msgBox.setText("ERROR: No connect!");
        msgBox.exec();
        return;
    }
    s->write(mes.toUtf8());

}

void MainWindow::on_micro_clicked()
{
    if(!isConnected)
        return;
    if(!isSoundRecorded)
    {
        //input->start(s);
        isSoundRecorded=true;
        QPixmap p(":/icons/micro1.png");
        QIcon icon(p);
        ui->micro->setIcon(icon);
        ui->micro->setIconSize(QSize(24,24));
    }
    else
    {
        //input->stop();
        isSoundRecorded=false;
        QPixmap p(":/icons/micro2.png");
        QIcon icon(p);
        ui->micro->setIcon(icon);
        ui->micro->setIconSize(QSize(24,24));
    }
    sendSpeech();
}

void MainWindow::on_sound_clicked()
{
    isLocked=!isLocked;
    if(isLocked)
    {
        QPixmap p(":/icons/sound2.png");
        QIcon icon(p);
        ui->sound->setIcon(icon);
        ui->sound->setIconSize(QSize(24,24));
    }
    else
    {
        QPixmap p(":/icons/sound1.png");
        QIcon icon(p);
        ui->sound->setIcon(icon);
        ui->sound->setIconSize(QSize(24,24));
    }
}

void MainWindow::sendSpeech()
{
    if(!isConnected)
        return;
    if(isSoundRecorded)
    {
        if(s->isOpen())
        {
            QString mes="talk";
            s->write(mes.toUtf8());
            input->start(s);
            device=output->start();
        }
        else
        {            
            input->stop();
        }
    }
    else
    {
        QString mes="quiet";
        s->write(mes.toUtf8());
        input->stop();
    }
}


void MainWindow::on_refresh_clicked()
{
    if(isConnected)
        on_connect_clicked();
    dlg.show();
    int st=dlg.exec();
    if(st==QDialog::Accepted)
    {

        dlg.player->stop();
        nick=dlg.getOut();
        address=dlg.getServer();
        port=dlg.getPORT().toInt();
    }
    else
    {
        dlg.player->stop();
        nick="user";
        address="0.0.0.0";
        port=8080;
    }
    if(nick.isEmpty())
    {
        nick="user";
    }
    if(address.isEmpty())
        address="0.0.0.0";
    if(port==0)
        port=8080;
    ui->address->setText(address);
    ui->address_2->setText(QString::number(port));
    ui->address_3->setText(nick);
}
