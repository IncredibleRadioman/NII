#include "qterminal.h"
#include <qdebug.h>



QTerminal::QTerminal(QWidget *parent):
    QTextEdit(parent)
{
    QPalette p = palette();
    p.setColor(QPalette::Base, Qt::white);
    p.setColor(QPalette::Text, Qt::black);
    setPalette(p);


    CommandList.clear();
    currentCommand=0;
    currentPosition=0;
    prefix="";
    textCursor().insertText(prefix);
}

void QTerminal::output(QString message)
{
    QTextCursor cursor = textCursor();

    cursor.movePosition(QTextCursor::StartOfBlock);

    cursor.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);

    cursor.removeSelectedText();
    cursor.insertText("<< "+message);

    setTextCursor(cursor);
    newBlock();
}



void QTerminal::keyPressEvent(QKeyEvent *e)
{
    //ввод обычных символов
    if(   e->key()>=0x20 && e->key()<=0x7e && (e->modifiers() == Qt::NoModifier || e->modifiers() == Qt::ShiftModifier) || (e->modifiers()==Qt::KeypadModifier))
    {
        QTextEdit::keyPressEvent(e);
        return;
    }
    if(e->key() == Qt::Key_Backspace
       && e->modifiers() == Qt::NoModifier
       && textCursor().positionInBlock() > prefix.length())
    {
        QTextEdit::keyPressEvent(e);
        return;
    }
    if(e->key() == Qt::Key_Return && e->modifiers() == Qt::NoModifier)
    {
        onEnter();
        return;
    }
//    if(e->key() == Qt::Key_Up && e->modifiers() == Qt::NoModifier)
//        prevHistory();
//    if(e->key() == Qt::Key_Down && e->modifiers() == Qt::NoModifier)
//        nextHistory();
    if(e->key() == Qt::Key_Left && e->modifiers() == Qt::NoModifier
            && textCursor().positionInBlock() > prefix.length())
    {
        QTextEdit::keyPressEvent(e);
        return;
    }

    if(e->key() == Qt::Key_Right && e->modifiers() == Qt::NoModifier)
    {
        QTextEdit::keyPressEvent(e);
        return;
    }
    else
        QTextEdit::keyPressEvent(e);
}

void QTerminal::mousePressEvent(QMouseEvent *)
{
    setFocus();
}

void QTerminal::mouseDoubleClickEvent(QMouseEvent *){}

void QTerminal::contextMenuEvent(QContextMenuEvent *){}

void QTerminal::onEnter()
{
    if(textCursor().positionInBlock() == prefix.length())
    {
        newBlock();
        return;
    }
    QString message=textCursor().block().text().mid(prefix.length());
    CommandList.append(message);
    currentCommand++;
    currentPosition=currentCommand;

    moveCursor(QTextCursor::EndOfBlock);
    newBlock();
    emit messageSended();
}

void QTerminal::prevHistory()
{
    if(currentCommand==0)
        return;
    if(currentPosition==0)
        return;

    QTextCursor cursor = textCursor();

    cursor.movePosition(QTextCursor::StartOfBlock);

    cursor.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);

    cursor.removeSelectedText();
    currentPosition--;
    cursor.insertText(prefix + CommandList.at(currentPosition));
    setTextCursor(cursor);

}

void QTerminal::nextHistory()
{
    //qDebug()<<"CP="<<currentPosition<<" CC="<<currentCommand;
    if(currentCommand==0)
        return;
    if(currentPosition==currentCommand)
        return;
    if(currentCommand-currentPosition == 1)
    {
        QTextCursor cursor = textCursor();

        cursor.movePosition(QTextCursor::StartOfBlock);

        cursor.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);

        cursor.removeSelectedText();
        cursor.insertText(prefix);

        setTextCursor(cursor);
        currentPosition++;
        return;
    }
    QTextCursor cursor = textCursor();

    cursor.movePosition(QTextCursor::StartOfBlock);

    cursor.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);

    cursor.removeSelectedText();
    currentPosition++;
    cursor.insertText(prefix + CommandList.at(currentPosition));
    setTextCursor(cursor);

}

void QTerminal::newBlock()
{
    //textCursor().block().text().clear();
    textCursor().insertBlock();

    textCursor().insertText(prefix);
    scrollDown();
    //qDebug()<<"NEW BLOCK";
}


void QTerminal::scrollDown()
{
    QScrollBar *vbar = verticalScrollBar();
    //vbar->setMaximum(this->geometry().width());
    vbar->setValue(vbar->maximum());
}
