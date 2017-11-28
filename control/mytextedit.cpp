#include "mytextedit.h"
//
//文本编辑控件
//
MyTextEdit::MyTextEdit(QWidget *parent) :
    QLineEdit(parent)
{
}

void MyTextEdit::keyPressEvent(QKeyEvent *k)
{
    //int pos=0;
    switch(k->key())
    {
       // case Qt::Key_Left: pos=this->cursorPosition(); pos--; this->setCursorPosition(pos); break;
       // case Qt::Key_Right: pos=this->cursorPosition(); pos++; this->setCursorPosition(pos); break;

        case Qt::Key_Return:
        case Qt::Key_Enter: this->close(); this->parentWidget()->setFocus(); break;
        default:
            QWidget::keyPressEvent(k); break;
    }
}
