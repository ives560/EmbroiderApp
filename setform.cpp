#include "setform.h"
#include "ui_setform.h"

SetForm::SetForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SetForm)
{
    ui->setupUi(this);

     CurSel=0;
    InitBackColor();

    InitSelectArray();
    InitWidgetsText();
    SelPlugin(0);
}

SetForm::~SetForm()
{
    delete ui;
}
//键盘按键事件
void SetForm::keyPressEvent(QKeyEvent *k)
{
    switch(k->key())
    {
        case Qt::Key_Escape: this->close(); break;
        case Qt::Key_1: SelPlugin(0);  break;
        case Qt::Key_2: SelPlugin(1); break;
        case Qt::Key_3: SelPlugin(2); break;
        case Qt::Key_4: SelPlugin(3); break;
        case Qt::Key_5: SelPlugin(4); break;
        case Qt::Key_6: SelPlugin(5); break;
        case Qt::Key_7: SelPlugin(6); break;
        case Qt::Key_8: SelPlugin(7); break;
        case Qt::Key_Up: ArrowsSelPlugin(false); break;
        case Qt::Key_Down: ArrowsSelPlugin(true); break;
        case Qt::Key_Return:
        case Qt::Key_Enter: PressEnterKey(CurSel); break;
    }
}
//按下回车键
void SetForm::PressEnterKey(int sel)
{
    SelectArray[sel]->PressEnterKey();
}
//设置背景颜色
void SetForm::InitBackColor()
{
    QPalette pa=palette();
    pa.setColor(QPalette::Window,QColor(100,100,255));
    this->setPalette(pa);
}
////初始化菜单项显示文字
void SetForm::InitSelectArray()
{
    SelectArray[0]=ui->widget;
    SelectArray[1]=ui->widget_2;
    SelectArray[2]=ui->widget_3;
    SelectArray[3]=ui->widget_4;
    SelectArray[4]=ui->widget_5;
    SelectArray[5]=ui->widget_6;
    SelectArray[6]=ui->widget_7;
    SelectArray[7]=ui->widget_8;

}
//初始化界面显示文字
void SetForm::InitWidgetsText()
{
    SelectArray[0]->label->setText(tr("1.针速:   针/分"));
    SelectArray[1]->label->setText(tr("2.针距:   mm"));
    SelectArray[2]->label->setText(tr("3.固缝针距:   mm"));
    SelectArray[3]->label->setText(tr("4.固缝长度:   mm"));
    SelectArray[4]->label->setText(tr("5.图形方向"));
    SelectArray[5]->label->setText(tr("6.系统参数"));
    SelectArray[6]->label->setText(tr("7.界限及出棚位置"));
    SelectArray[7]->label->setText(tr("8.花样边空"));
    //调整大小
    for(int i=0;i<8;i++)
    {
        SelectArray[i]->AdjustPluginSize();
    }
}
//改变选择新菜单项的颜色
void SetForm::SelPlugin(int sel)
{
    SelectArray[CurSel]->SelectFocusOut(QColor(100,100,255));//蓝色
    CurSel=sel;
    SelectArray[CurSel]->SelectFocusIn(QColor(255,255,255));//白色

}
//菜单项选择移动方向
//true为向下移动
//false为向上移动
void SetForm::ArrowsSelPlugin(bool UpDown)
{
    int newSel=CurSel;
    if(UpDown==true)//Down
    {
        newSel++;
        if(newSel==8)
            newSel=0;
        SelPlugin(newSel);
    }
    else if(UpDown==false)//Up
    {
        newSel--;
        if(newSel==-1)
            newSel=7;
        SelPlugin(newSel);
    }
}
