#ifndef MYTEXTEDIT_H
#define MYTEXTEDIT_H
//
//文本编辑控件
//
#include<QLineEdit>
#include<QKeyEvent>

class MyTextEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit MyTextEdit(QWidget *parent = 0);

protected:
    void keyPressEvent(QKeyEvent *);

signals:

public slots:

};

#endif // MYTEXTEDIT_H
