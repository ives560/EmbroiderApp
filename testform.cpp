#include "testform.h"
#include "ui_testform.h"

TestForm::TestForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TestForm)
{
    ui->setupUi(this);

    //设置背景颜色
    QPalette pa=palette();
    pa.setColor(QPalette::Window,QColor(100,100,255));
    this->setPalette(pa);
    startTimer(100);
}

TestForm::~TestForm()
{
    delete ui;
}

void TestForm::keyPressEvent(QKeyEvent *k)
{
    switch(k->key())
    {
        case Qt::Key_Escape: this->close(); break;

    }
}

//显示gpio状态信息
void TestForm::ShowText(int gpio, bool state)
{
    switch(gpio)
    {
        case KEY_MENU_RIGHT:
        {
            if(state==true)
                ui->label->setText("");
            else if(state==false)
                ui->label->setText("");
            break;
        }
        case KEY_BACK_ENTER:
        {
            if(state==true)
                ui->label->setText("");
            else if(state==false)
                ui->label->setText("");
            break;
        }
        case KEY_LEFT_DOWN:
        {
            if(state==true)
                ui->label->setText("");
            else if(state==false)
                ui->label->setText("");
            break;
        }
        default:
            break;
    }

}
