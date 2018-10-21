#include "dialog.h"
#include "ui_dialog.h"
#include <QUrl>
#include <QDir>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    connect(ui->pushButton,SIGNAL(clicked()),SLOT(accept()));
    player=new QMediaPlayer();
    connect(player, &QMediaPlayer::durationChanged, this, [&](qint64 dur){
        if(player->duration()==player->position())
            player->stop();
    });
    QString path=QDir::currentPath()+"/sounds/s.mp3";
    char* p=path.toLatin1().data();
    player->setMedia(QUrl::fromLocalFile(p));
    player->setVolume(20);
    player->play();
}

Dialog::~Dialog()
{
    delete ui;
}

QString Dialog::getOut()
{
    QString path=QDir::currentPath()+"/sounds/shao.mp3";
    char* p=path.toLatin1().data();
    player->setMedia(QUrl::fromLocalFile(p));
    player->setVolume(20);
    player->play();
    return ui->lineEdit->text();
}

QString Dialog::getServer()
{
    return ui->lineEdit_2->text();
}

QString Dialog::getPORT()
{
    return ui->lineEdit_3->text();
}

