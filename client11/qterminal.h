#ifndef QTERMINAL_H
#define QTERMINAL_H

//#include <QObject>
#include <QTextEdit>
#include <QtGui>
#include <QScrollBar>

class QTerminal : public QTextEdit
{
    Q_OBJECT
public:
    explicit QTerminal(QWidget *parent = 0);
    //~QTerminal();
    QStringList CommandList;
    int currentCommand;
    int currentPosition;
    QString prefix;
    void output(QString message);
protected:
    void keyPressEvent(QKeyEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseDoubleClickEvent(QMouseEvent *);
    void contextMenuEvent(QContextMenuEvent *);
    void onEnter();
    void prevHistory();
    void nextHistory();
    void newBlock();
    void scrollDown();
signals:
    void messageSended();
};

#endif // QTERMINAL_H
