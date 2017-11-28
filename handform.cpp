#include "handform.h"
#include "ui_handform.h"

HandForm::HandForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HandForm)
{
    ui->setupUi(this);

    //设置背景颜色
    QPalette pa=palette();
    pa.setColor(QPalette::Window,QColor(100,100,255));
    this->setPalette(pa);
}

HandForm::~HandForm()
{
    delete ui;
}
//键盘按键事件
void HandForm::keyPressEvent(QKeyEvent *k)
{
    switch(k->key())
    {
        case Qt::Key_Escape: this->close(); break;

    }
}
