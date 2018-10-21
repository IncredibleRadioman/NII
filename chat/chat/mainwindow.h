#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QAudioInput>
#include <QAudioFormat>
#include <QAudioDeviceInfo>
#include <QTcpSocket>
#include <QIODevice>
#include <QAudioOutput>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <dialog.h>
#include <QSound>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_connect_clicked();
    void receive();
    void sending();

    void on_micro_clicked();

    void on_sound_clicked();
    void sendSpeech();

    void on_refresh_clicked();

private:
    Ui::MainWindow *ui;
    QTcpSocket *s;
    QAudioInput* input;
    QAudioOutput* output;
    QIODevice *device;
    QTimer t;
    QTimer t1;

    QString nick;
    QString address;
    qint16 port;

    Dialog dlg;

    bool isConnected=false;
    bool isSoundRecorded=false;
    bool isLocked=false;
};

#endif // MAINWINDOW_H
