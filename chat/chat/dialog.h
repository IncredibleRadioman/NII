#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QMediaPlayer>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();
    QString getOut();
    QString getServer();
    QString getPORT();
    QMediaPlayer *player;

private:
    Ui::Dialog *ui;


};

#endif // DIALOG_H
