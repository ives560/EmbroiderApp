#include "widget.h"
#include "ui_widget.h"
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
   // this->showFullScreen();
    CurSel=0;
    InitSelectArray();
    InitWidgetsText();
    SelPlugin(0);

    m_devThread=new DevicesThread();
    ui->widget_7->m_devThread=m_devThread;//线程指针赋值
}

Widget::~Widget()
{
    delete m_devThread;
    delete ui;
}
//初始化花样装入窗口
void Widget::InitEnterForm()
{
    EnterForm *enterForm;

    enterForm=new EnterForm(this);
    enterForm->show();
    enterForm->move(0,50);
    enterForm->setFocus();
}
//初始化参数设置窗口
void Widget::InitSetForm()
{
    SetForm *setForm;
    setForm=new SetForm(this);
    setForm->show();
    setForm->move(30,50);
    setForm->setFocus();
}
//初始化手动移绷窗口
void Widget::InitHandForm()
{
    HandForm *handForm;
    handForm=new HandForm(this);
    handForm->show();
    handForm->move(160,50);
    handForm->setFocus();
}
////初始化系统测试窗口
void Widget::InitTestForm()
{
    TestForm *testForm;
    testForm=new TestForm(this);
    testForm->show();
    testForm->move(250,50);
    testForm->setFocus();
}
////初始化显示花样管理窗口
void Widget::InitManageForm()
{
    ManageForm *manageForm;

    manageForm=new ManageForm(this);
    manageForm->show();
    manageForm->move(0,50);
    manageForm->setFocus();
}
//键盘按键单击事件
void Widget::keyPressEvent(QKeyEvent *k)
{
        int c=-1;
        switch(k->key())
        {
            case Qt::Key_1:c=0; break;
            case Qt::Key_2:c=1; break;
            case Qt::Key_3:c=2; break;
            case Qt::Key_4:c=3; break;
            case Qt::Key_5:c=4; break;
            case Qt::Key_6:c=5; break;
            case Qt::Key_Left: ArrowsSelPlugin(false); break;
            case Qt::Key_Right: ArrowsSelPlugin(true); break;
            case Qt::Key_Return:
            case Qt::Key_Enter: SetPromptText(CurSel); PressEnterKey(CurSel); break;
            case Qt::Key_Escape: break;
            default:
                QWidget::keyPressEvent(k); break;
        }
        if(c>0)
        {
            SelPlugin(c);
            SetPromptText(CurSel);
            PressEnterKey(CurSel);
        }
}
//按下回车键
void Widget::PressEnterKey(int sel)
{
    switch(sel)
    {
        case 0:  InitEnterForm(); break;
        case 1:  InitSetForm(); break;
        case 2:  InitHandForm(); break;
        case 3:  InitTestForm(); break;
        case 4:  InitManageForm(); break;
        case 5: this->close(); break;
        default: break;
    }
}
//初始化菜单项数组
void Widget::InitSelectArray()
{
    SelectArray[0]=ui->widget;
    SelectArray[1]=ui->widget_2;
    SelectArray[2]=ui->widget_3;
    SelectArray[3]=ui->widget_4;
    SelectArray[4]=ui->widget_5;
    SelectArray[5]=ui->widget_6;

}
//初始化菜单项显示文字
void Widget::InitWidgetsText()
{
    SelectArray[0]->label->setText(tr("1.花样装入"));
    SelectArray[1]->label->setText(tr("2.参数设定"));
    SelectArray[2]->label->setText(tr("3.手动移棚"));
    SelectArray[3]->label->setText(tr("4.系统测试"));
    SelectArray[4]->label->setText(tr("5.花样管理"));
    SelectArray[5]->label->setText(tr("6.退出"));
    //调整大小
    for(int i=0;i<6;i++)
    {
        SelectArray[i]->AdjustPluginSize();
    }
}
//菜单项提示信息字符串
void Widget::SetPromptText(int sel)
{
    switch(sel)
    {
        case 0: ui->label_prompt->setText(tr("提示：输入花样的序号或按箭头键↑↓→←移动，按回车键确定选择，按ESC键退出。")); break;
        case 1: ui->label_prompt->setText(tr("提示：按数字键或按箭头键↑↓移动再按回车，选择要进行的操作，按ESC键返回。")); break;
        case 2: ui->label_prompt->setText(tr("提示：按箭头键↑↓→←移动，按F1键改变移动速度，按ESC键退出。")); break;
        case 3: ui->label_prompt->setText(tr("提示：开关各个传感器改变状态，按F1启动或停止主轴，F2或F3加减速主轴，ESC键退出。")); break;
        case 4: ui->label_prompt->setText(tr("提示：按数字键或按箭头键↑↓移动，再按回车键即可选择要进行的操作。")); break;
        case 5: ui->label_prompt->setText(tr("提示：退出。")); break;
        default: break;
    }
}
//改变选择新菜单项的颜色
void Widget::SelPlugin(int sel)
{
    SelectArray[CurSel]->SelectFocusOut(QColor(0,0,0,0));//无色
    CurSel=sel;
    SelectArray[CurSel]->SelectFocusIn(QColor(55,255,55));//绿色

}
//菜单项选择移动方向
//true为向右移动
//false为向左移动
void Widget::ArrowsSelPlugin(bool UpDown)
{
    int newSel=CurSel;
    if(UpDown==true)//Down
    {
        newSel++;
        if(newSel==6)
            newSel=0;
        SelPlugin(newSel);
    }
    else if(UpDown==false)//Up
    {
        newSel--;
        if(newSel==-1)
            newSel=5;
        SelPlugin(newSel);
    }
}
